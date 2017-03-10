#include "canvas.hh"
#include <cstdlib>
#include <iostream>
#include "fonts-manager.hh"


namespace og2
{

  Canvas::Canvas(SDL_Window* win)
    : renderer_(build_renderer_(win, -1,
                                SDL_RENDERER_ACCELERATED
                                | SDL_RENDERER_PRESENTVSYNC))
    , images_cache_(renderer_)
    , text_cache_(renderer_)
    , background_(Color::WHITE)
  {
  }

  Canvas::~Canvas()
  {
    SDL_DestroyRenderer(renderer_);
  }

  void Canvas::clear()
  {
    auto temp = color_get();
    color_set(background_);
    SDL_RenderClear(renderer_);
    color_set(temp);
  }
  
  void Canvas::render()
  {
    SDL_RenderPresent(renderer_);
  }

  Color Canvas::color_get() const
  {
    Color res;
    SDL_GetRenderDrawColor(renderer_, &(res.r), &(res.g),
                           &(res.b), &(res.a));
    return res;
  }

  void Canvas::color_set(const Color& c)
  {
    SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a);
  }

  void Canvas::draw_image(const char* path, const IRect& dims)
  {
    auto bdims = irect_box(dims);
    auto text = images_cache_.load(path);
    SDL_RenderCopy(renderer_, text.tex, nullptr, &bdims);
  }

  void Canvas::draw_image_clip(const char* path, const IRect& dims,
                               const IRect& clip_dims)
  {
    auto bdims = irect_box(dims);
    auto bclip_dims = irect_box(clip_dims);
    auto text = images_cache_.load(path);
    SDL_RenderCopy(renderer_, text.tex, &bclip_dims, &bdims);
  }

  void Canvas::draw_line(const IVector& from, const IVector& to)
  {
    SDL_RenderDrawLine(renderer_, from.x, from.y, to.x, to.y);
  }

  void Canvas::draw_polygon(const std::vector<IVector>& vertices)
  {
    for (std::size_t i = 0; i < vertices.size(); ++i)
      draw_line(vertices[i], vertices[(i + 1) % vertices.size()]);
  }

  void Canvas::draw_point(const IVector& pos)
  {
    SDL_RenderDrawPoint(renderer_, pos.x, pos.y);
  }
  
  void Canvas::draw_rect(const IVector& pos, const IVector& size)
  {
    SDL_Rect rect;
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = size.x;
    rect.h = size.y;
    SDL_RenderDrawRect(renderer_, &rect);
  }

  void Canvas::fill_rect(const IVector& pos, const IVector& size)
  {
    SDL_Rect rect;
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = size.x;
    rect.h = size.y;
    SDL_RenderFillRect(renderer_, &rect);
  }

  void Canvas::draw_text(const IVector& pos, const char* font, int size,
                         const Color& color, const std::string& text)
  {
    auto& fm = FontsManager::instance();
    auto ttf = fm.load(font, size);
    auto texture = text_cache_.load(text, color, ttf);

    SDL_Rect bdims;
    bdims.x = pos.x;
    bdims.y = pos.y;
    bdims.w = texture.w;
    bdims.h = texture.h;
    SDL_RenderCopy(renderer_, texture.tex, nullptr, &bdims);
  }

  IVector Canvas::text_size_get(const char* font, int size,
                                const Color& color, const std::string& text)
  {
    auto& fm = FontsManager::instance();
    auto ttf = fm.load(font, size);
    auto texture = text_cache_.load(text, color, ttf);
    return IVector{texture.w, texture.h};
  }

  IVector Canvas::image_size_get(const char* path)
  {
    auto tex = images_cache_.load(path);
    return IVector{tex.w, tex.h};
  }

  const Color& Canvas::background_get() const
  {
    return background_;
    
  }
  
  void Canvas::background_set(const Color& c)
  {
    background_ = c;
  }


  SDL_Renderer* Canvas::build_renderer_(SDL_Window* win, int index, Uint32 flags)
  {
    auto res = SDL_CreateRenderer(win, index, flags);
    if(!res)
			{
        std::cerr << "Error: CreateRenderer:"
                  << SDL_GetError() << "\n";
        exit(1);
			}
    return res;
  }

}
