#pragma once

#include <map>
#include <string>
#include "color.hh"
#include "sdl.hh"
#include "texture-infos.hh"

namespace og2
{

  class TextCache
  {

  public:
    TextCache(SDL_Renderer* renderer);
    TextCache(const TextCache&) = delete;
    TextCache& operator=(const TextCache&) = delete;
    ~TextCache();

    TextureInfos load(const std::string& text, const Color& c,
                      TTF_Font* font);

    void clear();
    


  private:

    struct Key
    {
      std::string text;
      Uint32 color;
      TTF_Font* font;

      bool operator<(const Key& k) const
      {
        if (color != k.color)
          return color < k.color;
        if (font != k.font)
          return font < k.font;
        else
          return text < k.text;
      }
    };

    std::map<Key, TextureInfos> textures_;
    SDL_Renderer* renderer_;
    
  };



}
