#include "text-cache.hh"
#include <cstdlib>
#include <iostream>


namespace og2
{

  TextCache::TextCache(SDL_Renderer* renderer)
    : renderer_(renderer)
  {}


  TextCache::~TextCache()
  {
    clear();
  }

  TextureInfos TextCache::load(const std::string& text, const Color& c,
                               TTF_Font* font)
  {
    Key key;
    key.text = text;
    key.color = c.to_u32();
    key.font = font;
    auto it = textures_.find(key);
    if (it != textures_.end())
      return it->second;

    auto tex = TextureInfos::build_text(renderer_, text, c, font);
    textures_[key] = tex;
    return tex;
  }


  void TextCache::clear()
  {
    for (auto it : textures_)
      SDL_DestroyTexture(it.second.tex);
  }

}
