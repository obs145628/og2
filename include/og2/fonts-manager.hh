#pragma once

#include <map>
#include <string>
#include "sdl.hh"

namespace og2
{

  class FontsManager
  {
  
  public:

    static FontsManager& instance();

    TTF_Font* load(const char* path, int size);

  private:

    struct Key
    {
      const char* path;
      int size;

      bool operator<(const Key& k) const
      {
        if (size != k.size)
          return size < k.size;
        else
          return path < k.path;
      }
    };

    std::map<Key, TTF_Font*> fonts_;
  
    FontsManager() = default;
    ~FontsManager();
    FontsManager(const FontsManager&) = delete;
    FontsManager& operator=(const FontsManager&) = delete;

  };
}
