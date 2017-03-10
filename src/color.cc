#include "color.hh"

namespace og2
{
  
  const Color Color::WHITE {0xFF, 0xFF, 0xFF};
  const Color Color::TRANSPARENT {0x0, 0x0, 0x0, 0x0};
  const Color Color::BLACK {0x0, 0x0, 0x0};
  const Color Color::RED {0xFF, 0x0, 0x0};
  const Color Color::GREEN {0x0, 0XFF, 0x0};
  const Color Color::BLUE {0x0, 0x0, 0xFF};
  const Color Color::YELLOW {0xFF, 0xFF, 0x0};
  const Color Color::CYAN {0x0, 0xFF, 0xFF};
  const Color Color::MAGENTA {0xFF, 0x0, 0xFF};

  Color::Color()
    : r(0xFF)
    , g(0xFF)
    , b(0xFF)
    , a(0xFF)
  {}
  
  Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : r(r)
    , g(g)
    , b(b)
    , a(a)
  {}

  Color::Color(const SDL_Color& c)
    : r(c.r)
    , g(c.g)
    , b(c.b)
    , a(c.a)
  {}

  Uint32 Color::to_u32() const
  {
    Uint32 res = (static_cast<Uint32> (a) << 24)
      | (static_cast<Uint32> (r) << 16)
      | (static_cast<Uint32> (g) << 8)
      | (static_cast<Uint32> (b) << 0);
    return res;
  }

  SDL_Color Color::box() const
  {
    SDL_Color res;
    res.r = r;
    res.g = g;
    res.b = b;
    res.a = a;
    return res;
  }


}
