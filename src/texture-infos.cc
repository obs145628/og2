#include "texture-infos.hh"
#include <cstdio>
#include <iostream>
#include "app.hh"
#include "path.hh"

namespace og2
{
  TextureInfos::TextureInfos(SDL_Texture* tex, int w, int h)
    : tex(tex)
    , w(w)
    , h(h)
  {
    
  }
  
  TextureInfos::TextureInfos(SDL_Renderer* renderer, SDL_Surface* surface)
  {
    tex = SDL_CreateTextureFromSurface(renderer, surface);
    if(!tex)
      {
        std::cerr << "Error: CreateTexture Failed: "
                  << SDL_GetError() << "\n";
        exit(1);
      }

    w = surface->w;
    h = surface->h;
  }

  TextureInfos TextureInfos::build_text(SDL_Renderer* renderer,
                                        const std::string& text, const Color& c,
                                        TTF_Font* font)
  {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), c.box());
    if (!surface)
      {
        std::cerr << "Error: Cannot load text surface: "
                  << TTF_GetError() << "\n";
        exit(1);
      }

    #ifdef RES_DEBUG
    std::cerr << "Debug: Load text '" << text << "'\n"; 
    #endif

    TextureInfos tex(renderer, surface);
    SDL_FreeSurface(surface);
    return tex;
  }

  TextureInfos TextureInfos::build_image(SDL_Renderer* renderer,
                                         const char* path)
  {
    auto tpath = Path::join(App::ressources_root_get(), path);
    SDL_Surface* surface = IMG_Load(tpath.c_str());
    if(!surface)
      {
        std::cerr << "Error: Canot load image " << path
                  << ": " << IMG_GetError() << "\n";
        exit(1);
      }

    #ifdef RES_DEBUG
    std::cerr << "Debug: Load image " << path << "\n"; 
    #endif

    TextureInfos tex(renderer, surface);
		SDL_FreeSurface(surface);
    return tex;
  }
}
