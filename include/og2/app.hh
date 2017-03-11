#pragma once

#include <string>
#include "vector.hh"

namespace og2
{

  class App
  {
  public:

    static const int IMG_FLAGS;

    static void init();
    static void quit();

    static const std::string& ressources_root_get();
    static void ressources_root_set(const std::string& path);

    static IVector screen_size_get();

  private:
    static std::string ressources_root_;
  };
  
}
