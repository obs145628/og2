#include "images-cache.hh"
#include <cstdlib>
#include <iostream>

namespace og2
{

  ImagesCache::ImagesCache(SDL_Renderer* renderer)
    : renderer_(renderer)
  {}

  TextureInfos ImagesCache::load(const char* path)
  {
    auto it = textures_.find(path);
    if (it != textures_.end())
      return it->second;

    auto tex = TextureInfos::build_image(renderer_, path);
    textures_.insert(std::make_pair(path, tex));
    return tex;
	}


  ImagesCache::~ImagesCache()
  {
    for (auto it : textures_)
      SDL_DestroyTexture(it.second.tex);
  }



}
