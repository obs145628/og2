#pragma once

#include <map>
#include <string>
#include "sdl.hh"
#include "texture-infos.hh"

namespace og2
{

  class ImagesCache
  {
  
  public:

    ImagesCache(SDL_Renderer* renderer);
    ~ImagesCache();
    ImagesCache(const ImagesCache&) = delete;
    ImagesCache& operator=(const ImagesCache&) = delete;
    

    TextureInfos load(const char* path);

  private:
    SDL_Renderer* renderer_;
    std::map<const char*, TextureInfos> textures_;
  


  };
}
