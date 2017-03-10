#pragma once

#include "rect.hh"

namespace og2
{

  template <class T>
  Rect<T>::Rect()
    : x(0)
    , y(0)
    , w(0)
    , h(0)
  {}

  template <class T>
  Rect<T>::Rect(const T& x, const T& y, const T& w, const T& h)
    : x(x)
    , y(y)
    , w(w)
    , h(h)
  {}

  template <class T>
  std::ostream& operator<<(std::ostream& os, const Rect<T>& r)
  {
    return os << '{' << r.x << ", " << r.y
              <<  ", " << r.w <<  ", " << r.h << '}';
  }
  
}
