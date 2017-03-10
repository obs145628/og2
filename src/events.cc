#include "events.hh"
#include "sdl.hh"

namespace og2
{
  const Uint32 Mouse::MASK_LEFT = SDL_BUTTON_LMASK;
  const Uint32 Mouse::MASK_MIDDLE = SDL_BUTTON_MMASK;
  const Uint32 Mouse::MASK_RIGHT = SDL_BUTTON_RMASK;
  const Uint32 Mouse::MASK_X1 = SDL_BUTTON_X1MASK;
  const Uint32 Mouse::MASK_X2 = SDL_BUTTON_X2MASK;

  const Uint8 Mouse::LEFT = SDL_BUTTON_LEFT;
  const Uint8 Mouse::MIDDLE = SDL_BUTTON_MIDDLE;
  const Uint8 Mouse::RIGHT = SDL_BUTTON_RIGHT;
  const Uint8 Mouse::X1 = SDL_BUTTON_X1;
  const Uint8 Mouse::X2 = SDL_BUTTON_X2;

  MouseMoveEvent::MouseMoveEvent(const SDL_MouseMotionEvent& e)
    : x(e.x)
    , y(e.y)
    , buttons(e.state)
  {}

  MouseClickEvent::MouseClickEvent(const SDL_MouseButtonEvent& e)
    : x(e.x)
    , y(e.y)
    , down(e.state == SDL_PRESSED)
    , clicks(e.clicks)
    , button(e.button)
  {}
  
}
