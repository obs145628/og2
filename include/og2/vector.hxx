#pragma once

#include "vector.hxx"


namespace og2
{

  template <class T>
  Vector<T>::Vector()
    : x(0)
    , y(0)
  {}
  
  template <class T>
  Vector<T>::Vector(T x, T y)
    : x(x)
    , y(y)
  {}


  template <class T>
  std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
  {
    return os << '{' << v.x << ", " << v.y << '}';
  }
  
}
