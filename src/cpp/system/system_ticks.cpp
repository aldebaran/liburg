/*!
  \file
  \brief �^�C���X�^���v�擾�֐�

  \author Satofumi KAMIMURA

  $Id: system_ticks.cpp 1053 2009-06-20 22:52:51Z satofumi $

  \todo �Đ����x�̕ύX�ɑΏ����邱��
*/

#include "SdlInit.h"
#include "system_ticks.h"
#include <SDL.h>

namespace
{
  class TicksInit : private qrk::SdlInit
  {
  };
}


int qrk::system_ticks(void)
{
  // �������p
  static TicksInit sdl_init;

  return SDL_GetTicks();
}
