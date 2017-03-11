#pragma once

#include "sdl.hh"
#include <string>
#include <vector>
#include "color.hh"
#include "images-cache.hh"
#include "rect.hh"
#include "text-cache.hh"
#include "vector.hh"

namespace og2
{

  class Canvas
  {
  public:

    Canvas(SDL_Window* win);
    Canvas(const Canvas&) = delete;
    Canvas& operator=(const Canvas&) = delete;
    ~Canvas();

    void clear();
    void render();
    
    Color color_get() const;
    void color_set(const Color& c);
    int thickness_get() const;
    void thickness_set(int thickness);

    void draw_circle(const IVector& center, int radius);
    void fill_circle(const IVector& center, int radius);
    
    void draw_image(const char* path, const IRect& dims);
    void draw_image_clip(const char* path, const IRect& dims,
                         const IRect& clip_dims);
    void draw_line(const IVector& from, const IVector& to);
    void draw_polygon(const std::vector<IVector>& vertices);
    void draw_point(const IVector& pos);
    void draw_rect(const IVector& pos, const IVector& size);
    void fill_rect(const IVector& pos, const IVector& size);
    void draw_text(const IVector& pos, const char* font, int size,
                   const Color& color, const std::string& text);

    IVector text_size_get(const char* font, int size,
                          const Color& color, const std::string& text);
    IVector image_size_get(const char* path);


    static SDL_Renderer* build_renderer_(SDL_Window* win, int index, Uint32 flags);

    const Color& background_get() const;
    void background_set(const Color& c);

    

  private:
    SDL_Renderer* renderer_;
    ImagesCache images_cache_;
    TextCache text_cache_;
    Color background_;
    int thickness_;
    
  };
  
}
