#pragma once

#include "sdl.hh"

namespace og2
{

  struct Mouse
  {
    static const Uint32 MASK_LEFT;
    static const Uint32 MASK_MIDDLE;
    static const Uint32 MASK_RIGHT;
    static const Uint32 MASK_X1;
    static const Uint32 MASK_X2;

    static const Uint8 LEFT;
    static const Uint8 MIDDLE;
    static const Uint8 RIGHT;
    static const Uint8 X1;
    static const Uint8 X2;
  };

  struct MouseMoveEvent
  {
    int x;
    int y;
    Uint32 buttons;

    MouseMoveEvent(const SDL_MouseMotionEvent& e);
  };

  struct MouseClickEvent
  {
    int x;
    int y;
    bool down;
    unsigned clicks;
    Uint8 button;

    MouseClickEvent(const SDL_MouseButtonEvent& e);
  };
  
}
