/*!
  \file
  \brief �^�C���X�^���v�擾�֐�

  \author Satofumi KAMIMURA

  $Id: ticks.cpp 1053 2009-06-20 22:52:51Z satofumi $
*/

#include "ticks.h"
#include "system_ticks.h"
#include "MonitorModeManager.h"


int qrk::ticks(void)
{
  // !!! delay() �Ƌ��ʂɂ��ׂ�
  static bool mode_unknown = true;
  static bool is_normal_delay = true;

  if (mode_unknown) {
    MonitorModeManager::MonitorMode mode =
      MonitorModeManager::object()->mode();
    if ((mode == MonitorModeManager::Play) ||
        (mode == MonitorModeManager::Simulation)) {
      is_normal_delay = false;
    }
    mode_unknown = false;
  }

  if (is_normal_delay) {
    return system_ticks();

  } else {
    // �Đ����A�V�~�����[�V�������́A
    // �B��� StopWatch ��p�������Ԃ�Ԃ��֐��Ƃ��ē��삷��
    // !!!
    // !!! ������
    return system_ticks();
  }
}
