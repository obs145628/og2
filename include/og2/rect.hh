#pragma once

#include <iostream>
#include "sdl.hh"

namespace og2
{

  template <class T>
  struct Rect
  {
    Rect();
    Rect(const T& x, const T& y, const T& w, const T& h);

    T x;
    T y;
    T w;
    T h;
  };

  template <class T>
  std::ostream& operator<<(std::ostream& os, const Rect<T>& rect);

  using IRect = Rect<int>;

  IRect irect_unbox(const SDL_Rect& rect);
  SDL_Rect irect_box(const IRect& rect);
  
}

#include "rect.hxx"
