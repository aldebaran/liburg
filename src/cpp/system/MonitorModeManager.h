#ifndef QRK_MONITOR_MODE_MANAGER_H
#define QRK_MONITOR_MODE_MANAGER_H

/*!
  \file
  \brief ���j�^�̃��[�h�Ǘ�

  \author Satofumi KAMIMURA

  $Id: MonitorModeManager.h 783 2009-05-05 08:56:26Z satofumi $
*/

#include <memory>


/*!
  \brief ���j�^�̃��[�h�Ǘ�

  �v���O�������s���ɓn���ꂽ�����ɂ��A���샂�[�h�����肷��B�P�x���肳�ꂽ���샂�[�h�́A�ύX�������Ȃ��B
*/
namespace qrk
{
  class MonitorModeManager
  {
    MonitorModeManager(void);
    MonitorModeManager(const MonitorModeManager& rhs);
    MonitorModeManager& operator = (const MonitorModeManager& rhs);

    struct pImpl;
    std::auto_ptr<pImpl> pimpl;

  public:

    // !!! �Ɨ��̃w�b�_�t�@�C���Ƃ��ĊǗ�����ׂ�
    typedef enum {
      Undefined,
      Record,
      Play,
      Simulation,
    } MonitorMode;

    ~MonitorModeManager(void);
    static MonitorModeManager* object(void);

    void setMode(int argc, char* argv[]);
    MonitorMode mode(void);
  };
}

#endif /* !QRK_MONITOR_MODE_MANAGER_H */
