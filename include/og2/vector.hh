#pragma once

#include <iostream>


namespace og2
{

  template <class T>
  struct Vector
  {

    Vector();
    Vector(T x, T y);

    T x;
    T y;
  };

  template <class T>
  std::ostream& operator<<(std::ostream& os, const Vector<T>& v);


  using IVector = Vector<int>;
}

#include "vector.hxx"
