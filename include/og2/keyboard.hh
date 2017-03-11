#pragma once

#include "sdl.hh"

namespace og2
{

  class Keyboard
  {
  public:
    static const Uint16 LSHIST;
    static const Uint16 RSHIFT;
    static const Uint16 LCTRL;
    static const Uint16 RCTRL;
    static const Uint16 LALT;
    static const Uint16 RALT;
    static const Uint16 LGUI;
    static const Uint16 RGUI;
    static const Uint16 NUM;
    static const Uint16 CAPS;
    static const Uint16 MODE;
    static const Uint16 CTRL;
    static const Uint16 SHIFT;
    static const Uint16 ALT;
    static const Uint16 GUI;

    static bool is_pressed(int code);
    static Uint16 mod_get();
  };

  struct KeyboardEvent
  {
    bool pressed;
    unsigned repeat;
    int code;
    Uint16 mod;

    KeyboardEvent(const SDL_KeyboardEvent& e);
  };
  
}
