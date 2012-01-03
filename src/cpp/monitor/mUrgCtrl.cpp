/*!
  \file
  \brief モニタ対応の URG 制御

  \author Satofumi KAMIMURA

  $Id: mUrgCtrl.cpp 1684 2010-02-10 23:56:38Z satofumi $
*/

#include "mUrgCtrl.h"
#include "RangeSensorParameter.h"
#include "UrgServer.h"
#include "SerialDevice.h"
#include "TcpipSocket.h"
#include "MonitorEventScheduler.h"
#include "MonitorDataHandler.h"
#include "LogNameHolder.h"
#include "DeviceIpManager.h"
#include "mConnection.h"

using namespace qrk;
using namespace std;


namespace
{
  class UrgCtrlForRecord : public UrgCtrl
  {
  public:
    MonitorModeManager::MonitorMode mode_;
    MonitorDataHandler* handler_;


    UrgCtrlForRecord(void) : handler_(NULL)
    {
    }


    ~UrgCtrlForRecord(void)
    {
      delete handler_;
    }


    void captureReceived(void)
    {
      // ダミーデータを記録し、取得タイミングを同期させる
      if ((mode_ == MonitorModeManager::Record) ||
          (mode_ == MonitorModeManager::Play)) {
        bool dummy = false;
        handler_->fetch(dummy);
      }
    }
  };
}


struct mUrgCtrl::pImpl
{
  MonitorModeManager::MonitorMode mode_;
  UrgCtrlForRecord* urg_;
  Connection* monitor_con_;
  Connection* device_con_;
  MonitorDataHandler* handler_;


  pImpl(void)
    : urg_(NULL), monitor_con_(NULL), device_con_(NULL), handler_(NULL)
  {
  }


  ~pImpl(void)
  {
    delete urg_;

    if (monitor_con_) {
      delete monitor_con_;
    }
    if (device_con_) {
      delete device_con_;
    }
    delete handler_;
  }


  void initializeConnection(int argc, char *argv[])
  {
    MonitorModeManager::object()->setMode(argc, argv);
    mode_ = MonitorModeManager::object()->mode();
    urg_->mode_ = mode_;

    // mConnection 用のログ管理
    if (mode_ != MonitorModeManager::Simulation) {
      device_con_ = new SerialDevice;
    } else {
      device_con_ = new TcpipSocket;
    }
    monitor_con_ = new mConnection(device_con_);
    urg_->setConnection(monitor_con_);

    // mUrgCtrl 用のログ管理
    string log_name = LogNameHolder::object()->name("mUrgCtrl");
    handler_ = new MonitorDataHandler(log_name, mode_);

    // データ取得スレッド用のログ管理
    log_name = LogNameHolder::object()->name("mUrgCtrl_thread");
    urg_->handler_ = new MonitorDataHandler(log_name, mode_);
  }
};


mUrgCtrl::mUrgCtrl(int argc, char *argv[]) : pimpl(new pImpl)
{
  pimpl->urg_ = new UrgCtrlForRecord;
  pimpl->initializeConnection(argc, argv);
}


mUrgCtrl::~mUrgCtrl(void)
{
}


const char* mUrgCtrl::what(void) const
{
  return pimpl->urg_->what();
}


bool mUrgCtrl::connect(const char* device, long baudrate)
{
  MonitorModeManager::MonitorMode Simulation = MonitorModeManager::Simulation;
  if (MonitorModeManager::object()->mode() == Simulation) {
    // device 名で IP ポート取得し、サーバを起動する
    long port = DeviceIpManager::object()->createIpPort(device);
    if (port > 0) {
      // IP ポートが取得済みでない場合のみ、サーバを起動する
      // !!! URG の型、シリアル ID の情報を、引数で反映させるべき
      UrgServer* urg_server = new UrgServer;
      if (! urg_server->activate(port)) {
        // サーバが起動できなければ、接続を中断する
        return false;
      }
      MonitorEventScheduler::object()->registerDeviceServer(urg_server);
    }
  }
  return pimpl->urg_->connect(device, baudrate);
}


void mUrgCtrl::setConnection(Connection* con)
{
  delete pimpl->monitor_con_;
  pimpl->monitor_con_ = new mConnection(con);
  pimpl->urg_->setConnection(pimpl->monitor_con_);
}


Connection* mUrgCtrl::connection(void)
{
  return pimpl->urg_->connection();
}


void mUrgCtrl::disconnect(void)
{
  pimpl->urg_->disconnect();
}


bool mUrgCtrl::isConnected(void) const
{
  return pimpl->urg_->isConnected();
}


long mUrgCtrl::minDistance(void) const
{
  return pimpl->urg_->minDistance();
}


long mUrgCtrl::maxDistance(void) const
{
  return pimpl->urg_->maxDistance();
}


int mUrgCtrl::maxScanLines(void) const
{
  return pimpl->urg_->maxScanLines();
}


void mUrgCtrl::setRetryTimes(size_t times)
{
  return pimpl->urg_->setRetryTimes(times);
}


int mUrgCtrl::scanMsec(void) const
{
  return pimpl->urg_->scanMsec();
}


void mUrgCtrl::setCaptureMode(RangeCaptureMode mode)
{
  pimpl->urg_->setCaptureMode(mode);
}


RangeCaptureMode mUrgCtrl::captureMode(void)
{
  return pimpl->urg_->captureMode();
}


void mUrgCtrl::setCaptureRange(int begin_index, int end_index)
{
  pimpl->urg_->setCaptureRange(begin_index, end_index);
}


void mUrgCtrl::setCaptureFrameInterval(size_t interval)
{
  pimpl->urg_->setCaptureFrameInterval(interval);
}


void mUrgCtrl::setCaptureTimes(size_t times)
{
  pimpl->urg_->setCaptureTimes(times);
}


size_t mUrgCtrl::remainCaptureTimes(void)
{
  return pimpl->urg_->remainCaptureTimes();
}


void mUrgCtrl::setCaptureSkipLines(size_t skip_lines)
{
  pimpl->urg_->setCaptureSkipLines(skip_lines);
}


int mUrgCtrl::capture(vector<long>& data, long* timestamp)
{
  // ダミーデータを記録し、取得タイミングを同期させる
  if ((pimpl->mode_ == MonitorModeManager::Record) ||
      (pimpl->mode_ == MonitorModeManager::Play)) {
    bool dummy = false;
    pimpl->handler_->fetch(dummy);
  }
  return pimpl->urg_->capture(data, timestamp);
}


int mUrgCtrl::captureWithIntensity(vector<long>& data,
                                   vector<long>& intensity_data,
                                   long* timestamp)
{
  // ダミーデータを記録し、取得タイミングを同期させる
  if ((pimpl->mode_ == MonitorModeManager::Record) ||
      (pimpl->mode_ == MonitorModeManager::Play)) {
    bool dummy = false;
    pimpl->handler_->fetch(dummy);
  }
  return pimpl->urg_->captureWithIntensity(data, intensity_data, timestamp);
}


void mUrgCtrl::stop(void)
{
  pimpl->urg_->stop();
}


bool mUrgCtrl::setTimestamp(int ticks, int* response_msec,
                            int* force_delay_msec)
{
  if ((pimpl->mode_ == MonitorModeManager::Record) ||
      (pimpl->mode_ == MonitorModeManager::Play)) {
    pimpl->handler_->fetch(ticks);
  }

  int recorded = (force_delay_msec) ? *force_delay_msec : 0;
  if (pimpl->mode_ == MonitorModeManager::Play) {
    pimpl->handler_->fetch(recorded);
  }

  int delay_msec = 0;
  bool ret = pimpl->urg_->setTimestamp(ticks, &delay_msec, &recorded);
  if (response_msec) {
    *response_msec = delay_msec;
  }
  if (pimpl->mode_ == MonitorModeManager::Record) {
    pimpl->handler_->fetch(delay_msec);
  }
  return ret;
}


bool mUrgCtrl::setLaserOutput(bool on)
{
  return pimpl->urg_->setLaserOutput(on);
}


double mUrgCtrl::index2rad(const int index) const
{
  return pimpl->urg_->index2rad(index);
}


int mUrgCtrl::rad2index(const double radian) const
{
  return pimpl->urg_->rad2index(radian);
}


void mUrgCtrl::setParameter(const RangeSensorParameter& parameter)
{
  pimpl->urg_->setParameter(parameter);
}


RangeSensorParameter mUrgCtrl::parameter(void) const
{
  return pimpl->urg_->parameter();
}


bool mUrgCtrl::versionLines(vector<string>& lines)
{
  return pimpl->urg_->versionLines(lines);
}


bool mUrgCtrl::loadParameter(void)
{
  return pimpl->urg_->loadParameter();
}


void mUrgCtrl::reboot(void)
{
  pimpl->urg_->reboot();
}


void mUrgCtrl::reset(void)
{
  pimpl->urg_->reset();
}
