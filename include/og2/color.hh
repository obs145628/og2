#pragma once

#include "sdl.hh"

namespace og2
{

  struct Color
  {
    static const Color WHITE;
    static const Color TRANSPARENT;
    static const Color BLACK;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color CYAN;
    static const Color MAGENTA;

    Color();
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF);
    Color(const SDL_Color& c);

    SDL_Color box() const;

    Uint32 to_u32() const;
    
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
  };
}
