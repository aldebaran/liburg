/*!
  \file
  \brief URG �Z���T����

  \author Satofumi KAMIMURA

  $Id: UrgCtrl.cpp 1669 2010-02-04 08:28:27Z satofumi $

  \todo remain_times �� 100 ���}�N���Œu��������
*/

#include "UrgCtrl.h"
#include "SerialDevice.h"
#include "ScipHandler.h"
#include "RangeSensorParameter.h"
#include "ticks.h"
#include "Thread.h"
#include "LockGuard.h"
#include "Lock.h"
#include <deque>
#include <limits>
#include <cstring>
#include <cstdio>

#ifdef MSC
#define snprintf _snprintf
#endif

using namespace qrk;
using namespace std;


namespace
{
  enum {
    MdScansMax = 100,           // [times]
  };
}


struct UrgCtrl::pImpl
{
  struct ScanData
  {
    vector<long> length_data;
    long timestamp;
    CaptureSettings settings;

    ScanData(void) : timestamp(-1)
    {
    }
  };


  class Capture
  {
  public:
    virtual ~Capture(void)
    {
    }

    virtual string createCaptureCommand(void) = 0;
    virtual int capture(vector<long>& data, long* timestamp) = 0;
    virtual void setCapturesSize(size_t size) = 0;
    virtual size_t capturesSize(void) = 0;
    virtual size_t remainCaptureTimes(void) = 0;
  };


  class RawManualCapture : public Capture
  {
    pImpl* pimpl_;

  public:
    RawManualCapture(pImpl* pimpl) : pimpl_(pimpl)
    {
    }


    ~RawManualCapture(void)
    {
    }


    string createCaptureCommand(void)
    {
      // !!! parameter ��M����ɁA����M�p�����[�^�ւ̑�����s��
      // !!! �����ł̑���M�ɂ́A����M�p�����[�^�̓��e��p����

      char buffer[] = "GDbbbbeeeegg\n";
      snprintf(buffer, strlen(buffer) + 1, "GD%04d%04d%02u\n",
               pimpl_->capture_begin_, pimpl_->capture_end_,
               pimpl_->capture_skip_lines_);

      return buffer;
    }


    int capture(vector<long>& data, long* timestamp)
    {
      pimpl_->retry_times_ = 0;

      // ���[�U��_�������Ă���
      pimpl_->scip_.setLaserOutput(ScipHandler::On);

      // �f�[�^�擾�R�}���h�̑��M
      string command = createCaptureCommand();
      int n = pimpl_->scip_.send(command.c_str(),
                                 static_cast<int>(command.size()));
      if (n != static_cast<int>(command.size())) {
        pimpl_->error_message_ = "Send command:" + command + " fail.";
        return -1;
      }

      CaptureSettings settings;
      pimpl_->scip_.receiveCaptureData(data, settings, timestamp, NULL);
      return static_cast<int>(data.size());
    }


    void setCapturesSize(size_t size)
    {
      static_cast<void>(size);

      // �������Ȃ�
    }


    size_t capturesSize(void)
    {
      return 1;
    }


    size_t remainCaptureTimes(void)
    {
      return 0;
    }
  };


  class RawAutoCapture : public Capture
  {
    pImpl* pimpl_;
    size_t captures_size_;


  public:
    RawAutoCapture(pImpl* pimpl) : pimpl_(pimpl), captures_size_(1)
    {
    }


    ~RawAutoCapture(void)
    {
    }


    string createCaptureCommand(void)
    {
      char buffer[] = "MDbbbbeeeeggstt\n";
      snprintf(buffer, strlen(buffer) + 1, "MD%04d%04d%02u%01u%02u\n",
               pimpl_->capture_begin_, pimpl_->capture_end_,
               pimpl_->capture_skip_lines_,
               pimpl_->capture_frame_interval_,
               (pimpl_->capture_times_ > 99) ? 0 : pimpl_->capture_times_);

      pimpl_->remain_times_ = pimpl_->capture_times_;

      return buffer;
    }


    int capture(vector<long>& data, long* timestamp)
    {
      if (pimpl_->retry_times_ > pimpl_->max_retry_times_) {
        return -1;
      }

      // �X���b�h���N��
      LockGuard guard(pimpl_->mutex_);
      if ((! pimpl_->thread_.isRunning()) && pimpl_->data_buffer_.empty()) {
        pimpl_->thread_.run(1);
      }

      // �擾�ς݃f�[�^���Ȃ���΁A�߂�
      if (pimpl_->data_buffer_.empty()) {
        if (pimpl_->invalid_packet_) {
          return -1;
        }
        return 0;
      }

      swap(data, pimpl_->data_buffer_.front().length_data);
      if (timestamp) {
        *timestamp = pimpl_->data_buffer_.front().timestamp;
      }
      pimpl_->data_buffer_.pop_front();

      return static_cast<int>(data.size());
    }


    void setCapturesSize(size_t size)
    {
      captures_size_ = size;
    }


    size_t capturesSize(void)
    {
      return captures_size_;
    }


    size_t remainCaptureTimes(void)
    {
      if (pimpl_->capture_times_ == 0) {
        return numeric_limits<size_t>::max();
      }

      LockGuard guard(pimpl_->mutex_);
      return pimpl_->remain_times_;
    }
  };


  class RawIntensityCapture : public Capture
  {
    pImpl* pimpl_;
    size_t captures_size_;


  public:
    RawIntensityCapture(pImpl* pimpl) : pimpl_(pimpl), captures_size_(1)
    {
    }


    ~RawIntensityCapture(void)
    {
    }


    string createCaptureCommand(void)
    {
      char buffer[] = "MEbbbbeeeeggstt\n";
      if ((! pimpl_->urg_type_.compare("URG-04LX")) ||
          (! pimpl_->urg_type_.compare("URG-04LX-UG01"))) {
        // URG-04LX �Ȃ�΁AFF �`���Ńf�[�^���M���s��
        snprintf(buffer, strlen(buffer) + 1, "MD%04d%04dFF%01u%02u\n",
                 pimpl_->capture_begin_, pimpl_->capture_end_,
                 pimpl_->capture_frame_interval_,
                 (pimpl_->capture_times_ > 99) ? 0 : pimpl_->capture_times_);

      } else {
        // UTM-30LX �Ȃ�΁AME �R�}���h��p����
        snprintf(buffer, strlen(buffer) + 1, "ME%04d%04d%02u%01u%02u\n",
                 pimpl_->capture_begin_, pimpl_->capture_end_,
                 pimpl_->capture_skip_lines_,
                 pimpl_->capture_frame_interval_,
                 (pimpl_->capture_times_ > 99) ? 0 : pimpl_->capture_times_);
      }
      pimpl_->remain_times_ = pimpl_->capture_times_;

      return buffer;
    }


    int capture(vector<long>& data, long* timestamp)
    {
      if (pimpl_->retry_times_ > pimpl_->max_retry_times_) {
        return -1;
      }

      LockGuard guard(pimpl_->mutex_);
      // �擾�ς݃f�[�^���Ȃ���΁A�X���b�h���N��
      if ((! pimpl_->thread_.isRunning()) && pimpl_->data_buffer_.empty()) {
        pimpl_->thread_.run(1);
      }

      // �擾�ς݃f�[�^���Ȃ���΁A�߂�
      if (pimpl_->data_buffer_.empty()) {
        if (pimpl_->invalid_packet_) {
          return -1;
        }
        return 0;
      }

      swap(data, pimpl_->data_buffer_.front().length_data);
      if (timestamp) {
        *timestamp = pimpl_->data_buffer_.front().timestamp;
      }
      CaptureSettings settings = pimpl_->data_buffer_.front().settings;
      pimpl_->data_buffer_.pop_front();
      pimpl_->intensity_data_.timestamp = *timestamp;
      pimpl_->intensity_data_.length_data.clear();

      if ((pimpl_->urg_type_.compare("URG-04LX")) &&
          (pimpl_->urg_type_.compare("URG-04LX-UG01"))) {
        // UTM-30LX �̂Ƃ�
        int skip_lines = settings.skip_lines;
        int min_length = pimpl_->parameters_.distance_min;
        int n = data.size() / skip_lines / 2;
        pimpl_->intensity_data_.length_data.reserve(n * skip_lines);

        int filled = 0;
        for (int i = 0; i < n; ++i) {
          size_t index = 2 * skip_lines * i;
          long length = data[index];
          long intensity_value =
            (length < min_length) ? 0 : data[index + skip_lines];
          for (int j = 0; j < skip_lines; ++j) {
            pimpl_->intensity_data_.length_data.push_back(intensity_value);
            data[filled++] = length;
          }
        }
        vector<long>::iterator first_it = data.begin() + (data.size() / 2);
        data.erase(first_it, data.end());

      } else if ((! pimpl_->urg_type_.compare("URG-04LX")) ||
                 (! pimpl_->urg_type_.compare("URG-04LX-UG01"))) {
        // URG-04LX �̂Ƃ�
        size_t n = data.size();
        int min_length = pimpl_->parameters_.distance_min;
        pimpl_->intensity_data_.length_data.reserve(data.size());
        size_t offset = pimpl_->capture_begin_ & 0x1;
        for (size_t i = 0; i < n; i += 2) {
          size_t index = i + offset;
          long length = data[index];
          if ((index + 1) < n) {
            long intensity_value = (length < min_length) ? 0 : data[index + 1];
            pimpl_->intensity_data_.length_data.push_back(intensity_value);
            pimpl_->intensity_data_.length_data.push_back(intensity_value);
            data[index + 1] = length;
          }
        }
      } else {
        // !!! �G���[����
      }

      return static_cast<int>(data.size());
    }


    void setCapturesSize(size_t size)
    {
      captures_size_ = size;
    }


    size_t capturesSize(void)
    {
      return captures_size_;
    }

    size_t remainCaptureTimes(void)
    {
      if (pimpl_->capture_times_ == 0) {
        return numeric_limits<size_t>::max();
      }

      LockGuard guard(pimpl_->mutex_);
      return pimpl_->remain_times_;
    }
  };


  string error_message_;
  UrgCtrl* parent_;
  Connection* con_;
  SerialDevice* serial_; //!< �L���Ȑڑ��I�u�W�F�N�g���Ȃ��Ƃ��ɗp����
  ScipHandler scip_;
  RangeSensorParameter parameters_;
  string urg_type_;
  long recent_timestamp_;
  int timestamp_offset_;

  RangeCaptureMode capture_mode_;
  RawManualCapture manual_capture_;
  RawAutoCapture auto_capture_;
  RawIntensityCapture intensity_capture_;
  Capture* capture_;
  Thread thread_;
  Lock mutex_;

  deque<ScanData> data_buffer_;
  ScanData intensity_data_;

  int capture_begin_;
  int capture_end_;
  size_t capture_skip_lines_;
  int capture_skip_frames_;

  size_t capture_frame_interval_;
  size_t capture_times_;
  size_t remain_times_;
  bool invalid_packet_;
  size_t max_retry_times_;
  size_t retry_times_;

  long base_timestamp_;
  long pre_timestamp_;


  pImpl(UrgCtrl* parent)
    : error_message_("no error."), parent_(parent),
      con_(NULL), serial_(NULL), urg_type_(""),
      recent_timestamp_(0), timestamp_offset_(0),
      capture_mode_(ManualCapture),
      manual_capture_(this), auto_capture_(this),
      intensity_capture_(this), capture_(&manual_capture_),
      thread_(&capture_thread, this),
      capture_begin_(0), capture_end_(0),
      capture_skip_lines_(1), capture_skip_frames_(0),
      capture_frame_interval_(0), capture_times_(0),
      remain_times_(0), invalid_packet_(false),
      max_retry_times_(DefaultRetryTimes), retry_times_(0),
      base_timestamp_(0), pre_timestamp_(0)
  {
  }


  ~pImpl(void)
  {
    disconnect();

    // con_ �͊O������Z�b�g�����\�������邽�߁A���̃N���X�ł͉�����Ȃ�
    // serial_ �̂݉������
    delete serial_;
  }


  void initializeSerial(void)
  {
    if (! serial_) {
      serial_ = new SerialDevice;
    }
    con_ = serial_;
  }


  bool connect(const char* device, long baudrate)
  {
    disconnect();
    if (! con_) {
      initializeSerial();
    }
    scip_.setConnection(con_);

    // �{�[���[�g�����o������ł̃f�o�C�X�Ƃ̐ڑ�
    if (! scip_.connect(device, baudrate)) {
      error_message_ = scip_.what();
      return false;
    }

    if (! loadParameter()) {
      return false;
    }
    updateCaptureParameters();

    return true;
  }


  bool loadParameter(void)
  {
    // URG �p�����[�^�̎擾
    RangeSensorParameter parameters;
    if (! scip_.loadParameter(parameters)) {
      error_message_ = scip_.what();
      return false;
    }
    swap(parameters_, parameters);

    size_t type_length = parameters_.model.find('(');
    urg_type_ = parameters_.model.substr(0, type_length);

    // !!! capture_begin_, capture_end_ �Ƃ̒��������ׂ�
    // !!! min(), max() ���g������

    return true;
  }


  void disconnect(void)
  {
    stop();
    if (con_) {
      con_->disconnect();
    }
  }


  void updateCaptureParameters(void)
  {
    capture_begin_ = parameters_.area_min;
    capture_end_ = parameters_.area_max;
  }


  // AutoCapture, IntensityCapture �̃f�[�^�擾���s��
  static int capture_thread(void* args)
  {
    pImpl* obj = static_cast<pImpl*>(args);

    // �ݒ�Ɋ�Â��āA�f�[�^��M�R�}���h���쐬���Ĕ��s
    string capture_command = obj->capture_->createCaptureCommand();
    if (capture_command.empty()) {
      // �����̃G���[�� IntensityCapture �̂Ƃ��̂ݔ�������̂Ɉˑ���������
      obj->error_message_ = "This urg is not support intensity capture.";
      return -1;
    }
    int n = obj->scip_.send(capture_command.c_str(),
                            static_cast<int>(capture_command.size()));
    if (n != static_cast<int>(capture_command.size())) {
      obj->error_message_ = capture_command + " fail.";
      ++obj->retry_times_;
      return -1;
    }

    // ��M�҂�
    ScanData data;
    int remain_times = MdScansMax;
    int total_times = 0;
    while (1) {
      // ��M�����A����уG���[�Ŕ�����
      obj->invalid_packet_ = false;
      CaptureType type =
        obj->scip_.receiveCaptureData(data.length_data, data.settings,
                                      &data.timestamp,
                                      &remain_times, &total_times);
      if (type == Mx_Reply) {
        // MS/MD �̉����p�P�b�g�̏ꍇ�A���̃f�[�^��҂�
        continue;
      }

      if (! ((type == MD) || (type == MS) || (type == ME))) {
        // ��M�f�[�^�łȂ���΁A�X���b�h�����𒆒f����
        obj->invalid_packet_ = true;
        ++obj->retry_times_;
        break;
      }
      obj->retry_times_ = 0;

      // �^�C���X�^���v�� 24 bit �����Ȃ����߁A�P�����邱�Ƃւ̑Ώ�
      if ((data.timestamp >= 0) && (data.timestamp < obj->pre_timestamp_)) {
        obj->base_timestamp_ += 1 << 24;
      }
      obj->pre_timestamp_ = data.timestamp;
      data.timestamp += obj->base_timestamp_;

      LockGuard guard(obj->mutex_);
      deque<ScanData>& data_buffer = obj->data_buffer_;

      // �Â��Ȃ����f�[�^����菜��
      int current_size = static_cast<int>(data_buffer.size());
      int erase_size =
        current_size - static_cast<int>(obj->capture_->capturesSize());
      if (erase_size > 0) {
        data_buffer.erase(data_buffer.begin(),
                          data_buffer.begin() + erase_size);
      }

      // ����̃f�[�^��ǉ�
      ScanData dummy_data;
      data_buffer.push_back(dummy_data);
      swap(data_buffer.back(), data);

      if ((obj->capture_times_ > 0) && (remain_times < MdScansMax)) {
        obj->remain_times_ = remain_times;
      } else {
        --obj->remain_times_;
        if (obj->remain_times_ == 0) {
          obj->scip_.setLaserOutput(Off);
        }
      }
      obj->parent_->captureReceived();

      if ((total_times > 0) && (remain_times == 0)) {
        // �擾���I��������A������
        break;
      }
    }

    return 0;
  }


  int capture(vector<long>& data, long* timestamp)
  {
    long raw_timestamp = 0;
    int n = capture_->capture(data, &raw_timestamp);
    if (n < 0) {
      error_message_ = scip_.what();
      return n;
    }

    if (timestamp) {
      *timestamp = raw_timestamp - timestamp_offset_;
      recent_timestamp_ = *timestamp;
    }
    return n;
  }


  int captureWithIntensity(vector<long>& data,
                           vector<long>& intensity_data,
                           long* timestamp)
  {
    int n = capture(data, timestamp);
    if (n < 0) {
      return n;
    }
    return captureIntensity(intensity_data, NULL);
  }


  int captureIntensity(vector<long>& intensity_data, int* timestamp)
  {
    if (capture_mode_ != IntensityCapture) {
      error_message_ = "please call setCaptureMode(IntensityCapture).";
      return -1;
    }

    if (intensity_data_.length_data.empty()) {
      return 0;
    }

    if (timestamp) {
      *timestamp = intensity_data_.timestamp;
      recent_timestamp_ = *timestamp;
    }
    swap(intensity_data, intensity_data_.length_data);
    intensity_data_.length_data.clear();

    return static_cast<int>(intensity_data.size());
  }


  bool setTimestamp(int timestamp, int* response_msec, int* force_delay_msec)
  {
    // TM0 ���[�h�ɑJ��
    // !!! true, false ���L�[���[�h�Œu�����邱��
    if (! scip_.setRawTimestampMode(true)) {
      return false;
    }

    // TM1 �̃^�C���X�^���v���擾���A�ʐM�x���� URG �̃^�C���X�^���v���擾����
    int urg_timestamp = 0;
    int first_ticks = ticks();
    if (scip_.rawTimestamp(&urg_timestamp)) {
      int delay = ticks() - first_ticks;
      if (force_delay_msec) {
        delay = *force_delay_msec;
      }
      if (response_msec) {
        *response_msec = delay;
      }
      timestamp_offset_ =  urg_timestamp - timestamp + delay;
    }

    // URG �^�C���X�^���v�p�̃I�t�Z�b�g���Ԃ��v�Z���ATM2 �Ŕ�����
    if (! scip_.setRawTimestampMode(false)) {
      return false;
    }

    return true;
  }


  int rad2index(const double radian) const
  {
    int area_total = parameters_.area_total;
    int index =
      static_cast<int>(floor(((radian * area_total) / (2.0 * M_PI)) + 0.5)
                       + parameters_.area_front);

    if (index < 0) {
      index = 0;
    } else if (index > parameters_.area_max) {
      index = parameters_.area_max;
    }
    return index;
  }


  bool isConnected(void) const
  {
    return (con_ == NULL) ? false : con_->isConnected();
  }


  void stop(void)
  {
    if (! isConnected()) {
      return;
    }

    if (capture_mode_ == ManualCapture) {
      return;
    }

    // QT �R�}���h�̔��s
    scip_.setLaserOutput(ScipHandler::Off);

    // ������҂�
    if (thread_.isRunning()) {
      thread_.wait();
    }
  }


  void clear(void)
  {
    LockGuard guard(mutex_);
    data_buffer_.clear();
    intensity_data_.length_data.clear();
  }
};


UrgCtrl::UrgCtrl(void) : pimpl(new pImpl(this))
{
}


UrgCtrl::~UrgCtrl(void)
{
}


void UrgCtrl::captureReceived(void)
{
  // ��M�������p����̃N���X�����p���邽�߂̃��\�b�h
}


const char* UrgCtrl::what(void) const
{
  return pimpl->error_message_.c_str();
}


bool UrgCtrl::connect(const char* device, long baudrate)
{
  return pimpl->connect(device, baudrate);
}


void UrgCtrl::setConnection(Connection* con)
{
  pimpl->serial_ = NULL;
  pimpl->con_ = con;
  pimpl->scip_.setConnection(con);
}


Connection* UrgCtrl::connection(void)
{
  return pimpl->con_;
}


void UrgCtrl::disconnect(void)
{
  pimpl->disconnect();
}


bool UrgCtrl::isConnected(void) const
{
  return pimpl->isConnected();
}


long UrgCtrl::minDistance(void) const
{
  return pimpl->parameters_.distance_min;
}


long UrgCtrl::maxDistance(void) const
{
  return pimpl->parameters_.distance_max;
}


int UrgCtrl::maxScanLines(void) const
{
  // +1 �́Aparameters_ �����������̂Ƃ��� new long [0] ���Ȃ����߂̏��u
  return pimpl->parameters_.area_max + 1;
}


void UrgCtrl::setRetryTimes(size_t times)
{
  pimpl->max_retry_times_ = times;
}


void UrgCtrl::setCapturesSize(size_t size)
{
  pimpl->capture_->setCapturesSize(size);
}


size_t UrgCtrl::remainCaptureTimes(void)
{
  return pimpl->capture_->remainCaptureTimes();
}


int UrgCtrl::scanMsec(void) const
{
  int scan_rpm = pimpl->parameters_.scan_rpm;
  return (scan_rpm <= 0) ? 1 : (1000 * 60 / scan_rpm);
}


void UrgCtrl::setCaptureMode(RangeCaptureMode mode)
{
  // capture ���~����Bcapture �̍ĊJ�͍s��Ȃ�
  stop();
  pimpl->clear();

  if (mode == ManualCapture) {
    pimpl->capture_ = &pimpl->manual_capture_;

  } else if (mode == AutoCapture) {
    pimpl->capture_ = &pimpl->auto_capture_;

  } else if (mode == IntensityCapture) {
    pimpl->capture_ = &pimpl->intensity_capture_;
  }

  pimpl->capture_mode_ = mode;
}


RangeCaptureMode UrgCtrl::captureMode(void)
{
  return pimpl->capture_mode_;
}


void UrgCtrl::setCaptureRange(int begin_index, int end_index)
{
  // !!! �r������

  // capture ���~����Bcapture �̍ĊJ�͍s��Ȃ�
  stop();
  pimpl->clear();

  pimpl->capture_begin_ = begin_index;
  pimpl->capture_end_ = end_index;
}


void UrgCtrl::setCaptureFrameInterval(size_t interval)
{
  // !!! �r������

  // capture ���~����Bcapture �̍ĊJ�͍s��Ȃ�
  stop();
  pimpl->clear();

  pimpl->capture_frame_interval_ = interval;
}


void UrgCtrl::setCaptureTimes(size_t times)
{
  // !!! �r������

  // capture ���~����Bcapture �̍ĊJ�͍s��Ȃ�
  stop();
  pimpl->clear();

  // !!! �͈͐����̔��菈��
  pimpl->capture_times_ = times;
}



void UrgCtrl::setCaptureSkipLines(size_t skip_lines)
{
  // capture ���~����Bcapture �̍ĊJ�͍s��Ȃ�
  stop();
  pimpl->clear();

  pimpl->capture_skip_lines_ = skip_lines;
}


int UrgCtrl::capture(vector<long>& data, long* timestamp)
{
  // !!! ���ڑ��Ȃ�΁A�߂�

  return pimpl->capture(data, timestamp);
}


int UrgCtrl::captureWithIntensity(vector<long>& data,
                                  vector<long>& intensity_data,
                                  long* timestamp)
{
  // !!! ���ڑ��Ȃ�΁A�߂�
  return pimpl->captureWithIntensity(data, intensity_data, timestamp);
}


void UrgCtrl::stop(void)
{
  pimpl->stop();
}


bool UrgCtrl::setTimestamp(int ticks, int* response_msec, int* force_delay_msec)
{
  // !!! ���ڑ��Ȃ�΁A�߂�

  return pimpl->setTimestamp(ticks, response_msec, force_delay_msec);
}


long UrgCtrl::recentTimestamp(void) const
{
  return pimpl->recent_timestamp_;
}


bool UrgCtrl::setLaserOutput(bool on)
{
  // !!! ���ڑ��Ȃ�΁A�߂�

  return pimpl->scip_.setLaserOutput(on, ScipHandler::Force);
}


double UrgCtrl::index2rad(const int index) const
{
  int index_from_front = index - pimpl->parameters_.area_front;
  return index_from_front * (2.0 * M_PI) / pimpl->parameters_.area_total;
}


int UrgCtrl::rad2index(const double radian) const
{
  return pimpl->rad2index(radian);
}


void UrgCtrl::setParameter(const RangeSensorParameter& parameter)
{
  pimpl->parameters_ = parameter;
  pimpl->updateCaptureParameters();
}


RangeSensorParameter UrgCtrl::parameter(void) const
{
  return pimpl->parameters_;
}


bool UrgCtrl::loadParameter(void)
{
  return pimpl->loadParameter();
}


bool UrgCtrl::versionLines(vector<string>& lines)
{
  if (! isConnected()) {
    return false;
  }

  return pimpl->scip_.versionLines(lines);
}


bool UrgCtrl::reboot(void)
{
  UrgCtrl::setLaserOutput(Off);

  // send "RB" twice.
  for (int i = 0; i < 2; ++i) {
    pimpl->scip_.send("RB\n", 3);

    enum {
      RB_Timeout = 1000,        // [msec]
    };
    char recv_buffer[3];
    int send_n = pimpl->scip_.recv(recv_buffer, 3, RB_Timeout);
    if (send_n != 3) {
      return false;
    }
    if (strncmp(recv_buffer, "RB\n", 3)) {
      return false;
    }
  }

  UrgCtrl::disconnect();

  return true;
}


bool UrgCtrl::reset(void)
{
  return reboot();
}
