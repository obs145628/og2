#include "keyboard.hh"

namespace og2
{

  const Uint16 Keyboard::LSHIST = KMOD_LSHIFT;
  const Uint16 Keyboard::RSHIFT = KMOD_RSHIFT;
  const Uint16 Keyboard::LCTRL = KMOD_LCTRL;
  const Uint16 Keyboard::RCTRL = KMOD_RCTRL;
  const Uint16 Keyboard::LALT = KMOD_LALT;
  const Uint16 Keyboard::RALT = KMOD_RALT;
  const Uint16 Keyboard::LGUI = KMOD_LGUI;
  const Uint16 Keyboard::RGUI = KMOD_RGUI;
  const Uint16 Keyboard::NUM = KMOD_NUM;
  const Uint16 Keyboard::CAPS = KMOD_CAPS;
  const Uint16 Keyboard::MODE = KMOD_MODE;
  const Uint16 Keyboard::CTRL = KMOD_CTRL;
  const Uint16 Keyboard::SHIFT = KMOD_SHIFT;
  const Uint16 Keyboard::ALT = KMOD_ALT;
  const Uint16 Keyboard::GUI = KMOD_GUI;

  bool Keyboard::is_pressed(int code)
  {
    int len;
    auto arr = SDL_GetKeyboardState(&len);
    if (code < 0 || code >= len)
      return false;
    return arr[code];
  }

  KeyboardEvent::KeyboardEvent(const SDL_KeyboardEvent& e)
    : pressed(e.state == SDL_PRESSED)
    , repeat(e.repeat)
    , code(e.keysym.sym)
    , mod(e.keysym.mod)
  {}
  
}
