#pragma once

#include <string>
#include "color.hh"
#include "sdl.hh"

namespace og2
{

  struct TextureInfos
  {
    TextureInfos() = default;
    TextureInfos(SDL_Texture* tex, int w, int h);
    TextureInfos(SDL_Renderer* renderer, SDL_Surface* surface);

    static TextureInfos build_text(SDL_Renderer* renderer,
                                   const std::string& text, const Color& c,
                                   TTF_Font* font);

    static TextureInfos build_image(SDL_Renderer* renderer,
                                    const char* path);

    

    SDL_Texture* tex;
    int w;
    int h;
  };
  
}
