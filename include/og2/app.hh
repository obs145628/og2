#pragma once

#include <string>

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

  private:
    static std::string ressources_root_;
  };
  
}
