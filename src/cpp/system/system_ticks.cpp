/*!
  \file
  \brief タイムスタンプ取得関数

  \author Satofumi KAMIMURA

  $Id: system_ticks.cpp 1053 2009-06-20 22:52:51Z satofumi $

  \todo 再生速度の変更に対処すること
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
  // 初期化用
  static TicksInit sdl_init;

  return SDL_GetTicks();
}
