#include "canvas.hh"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>
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
    , thickness_(1)
  {}

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

  double Canvas::thickness_get() const
  {
    return thickness_;
  }
  
  void Canvas::thickness_set(double thickness)
  {
    thickness_ = thickness;
  }

  //Bresenham's circle algorithm
  void Canvas::draw_circle(const IVector& center, int radius)
  {
    int x0 = center.x;
    int y0 = center.y;
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
      draw_point(IVector{x0 + x, y0 + y});
      draw_point(IVector{x0 + y, y0 + x});
      draw_point(IVector{x0 - y, y0 + x});
      draw_point(IVector{x0 - x, y0 + y});
      draw_point(IVector{x0 - x, y0 - y});
      draw_point(IVector{x0 - y, y0 - x});
      draw_point(IVector{x0 + y, y0 - x});
      draw_point(IVector{x0 + x, y0 - y});

      if (err <= 0)
        err += 2*(++y) + 1;
      if (err > 0)
        err -= 2*(--x) + 1;
    }
  }

  void Canvas::fill_circle(const IVector& center, int radius)
  {
    int x0 = center.x;
    int y0 = center.y;
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
      {
        SDL_RenderDrawLine(renderer_, x0 + x, y0 + y,
                           x0 - x, y0 + y);
        SDL_RenderDrawLine(renderer_, x0 + y, y0 + x,
                           x0 - y, y0 + x);
        SDL_RenderDrawLine(renderer_, x0 - x, y0 - y,
                           x0 + x, y0 - y);
        SDL_RenderDrawLine(renderer_, x0 - y, y0 - x,
                           x0 + y, y0 - x); 

        if (err <= 0)
          err += 2*(++y) + 1;
        if (err > 0)
          err -= 2*(--x) + 1;
      }
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
    if (thickness_ == 1)
      SDL_RenderDrawLine(renderer_, from.x, from.y, to.x, to.y);
    else
      draw_thick_line_(from.x, from.y, to.x, to.y, thickness_);
  }

  void Canvas::draw_polygon(const std::vector<IVector>& vertices)
  {
    for (std::size_t i = 0; i < vertices.size(); ++i)
      draw_line(vertices[i], vertices[(i + 1) % vertices.size()]);
  }

  void Canvas::fill_polygon(const std::vector<IVector>& vertices)
  {
    if (vertices.empty())
      return;
    int ymin = vertices[0].y;
    int ymax = vertices[0].y;
    int xmin = vertices[0].x;
    int xmax = vertices[0].x;
    for (const auto& v : vertices)
      {
        if (v.y < ymin)
          ymin = v.y;
        if (v.y > ymax)
          ymax = v.y;
        if (v.x < xmin)
          xmin = v.x;
        if (v.x > xmax)
          xmax = v.x;
      }

    for (int y = ymin; y <= ymax; ++y)
      {
        std::set<int> dots;
        for (std::size_t i = 0; i < vertices.size(); ++i)
          {
            const auto& p1 = vertices[i];
            const auto& p2 = vertices[(i + 1) % vertices.size()];

            if (p1.y == y && p2.y == y)
              {
                dots.insert(p1.x);
                dots.insert(p2.x);
                continue;
              }
            
            auto inter =  line_intersects_(xmin, y, xmax, y,
                                           p1.x, p1.y, p2.x, p2.y);
            if (inter.first)
              dots.insert(inter.second.x);
          }

        std::vector<int> vdots(dots.begin(), dots.end());
        if (vdots.empty())
          continue;
        for (std::size_t i = 0; i < vdots.size() - 1; i += 2)
          SDL_RenderDrawLine(renderer_, vdots[i], y, vdots[i + 1], y);
      }

    
  }

  void Canvas::draw_point(const IVector& pos)
  {
    if (thickness_ <= 1)
      SDL_RenderDrawPoint(renderer_, pos.x, pos.y);
    else
      draw_thick_line_(pos.x, pos.y, pos.x, pos.y, thickness_);
  }
  
  void Canvas::draw_rect(const IVector& pos, const IVector& size)
  {
    draw_line(IVector{pos.x, pos.y}, IVector{pos.x + size.x, pos.y});
    draw_line(IVector{pos.x + size.x, pos.y}, IVector{pos.x + size.x, pos.y + size.y});
    draw_line(IVector{pos.x + size.x, pos.y + size.y}, IVector{pos.x, pos.y + size.y});
    draw_line(IVector{pos.x, pos.y + size.y}, IVector{pos.x, pos.y});
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

  void Canvas::draw_ellipse(const IVector& pos, const IVector& size)
  {
    int x0 = pos.x;
    int y0 = pos.y;
    int w = size.x;
    int h = size.y;
    int w2 = w * w;
    int h2 = h * h;
    int fw2 = 4 * w2;
    int fh2 = 4 * h2;
    for (int x = 0, y = h, s = 2 * h2 + w2 *(1 - 2 * h);
         h2 * x <= w2 * y;
         ++x)
      {
        draw_point(IVector{x0 + x, y0 + y});
        draw_point(IVector{x0 - x, y0 + y});
        draw_point(IVector{x0 + x, y0 - y});
        draw_point(IVector{x0 - x, y0 - y});
        if (s >= 0)
          {
            s += fw2 * (1 - y--);
          }
        s += h2 * ((4 * x) + 6);
      }
    for (int x = w, y = 0, s = 2 * w2 + h2 * (1 - 2 * w);
         w2 * y <= h2 * x;
         ++y)
      {
        draw_point(IVector{x0 + x, y0 + y});
        draw_point(IVector{x0 - x, y0 + y});
        draw_point(IVector{x0 + x, y0 - y});
        draw_point(IVector{x0 - x, y0 - y});
        if (s >= 0)
          {
            s += fh2 * (1 - x--);
          }
        s += w2 * ((4 * y) + 6);
      }
  }

  void Canvas::fill_ellipse(const IVector& pos, const IVector& size)
  {
    int x0 = pos.x;
    int y0 = pos.y;
    int w = size.x;
    int h = size.y;
    int w2 = w * w;
    int h2 = h * h;
    int fw2 = 4 * w2;
    int fh2 = 4 * h2;
    for (int x = 0, y = h, s = 2 * h2 + w2 *(1 - 2 * h);
         h2 * x <= w2 * y;
         ++x)
      {
        SDL_RenderDrawLine(renderer_, x0 + x, y0 + y,
                           x0 - x, y0 + y);
        SDL_RenderDrawLine(renderer_, x0 + x, y0 - y,
                           x0 - x, y0 - y);
        if (s >= 0)
          {
            s += fw2 * (1 - y--);
          }
        s += h2 * ((4 * x) + 6);
      }
    for (int x = w, y = 0, s = 2 * w2 + h2 * (1 - 2 * w);
         w2 * y <= h2 * x;
         ++y)
      {
        SDL_RenderDrawLine(renderer_, x0 + x, y0 + y,
                           x0 - x, y0 + y);
        SDL_RenderDrawLine(renderer_, x0 + x, y0 - y,
                           x0 - x, y0 - y);
        if (s >= 0)
          {
            s += fh2 * (1 - x--);
          }
        s += w2 * ((4 * y) + 6);
      }
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

  void Canvas::draw_thick_line_(int x0, int y0, int x1, int y1, double tk)
  {

    std::vector<IVector> p(4);
    double angle = std::atan2(y1 - y0, x1 - x0);
    p[0].x = x0 + tk / 2 * std::cos(angle + M_PI/2);
    p[0].y = y0 + tk / 2 * std::sin(angle + M_PI/2);
    p[1].x = x0 + tk / 2 * std::cos(angle - M_PI/2);
    p[1].y = y0 + tk / 2 * std::sin(angle - M_PI/2);
    p[2].x = x1 + tk / 2 * std::cos(angle - M_PI/2);
    p[2].y = y1 + tk / 2 * std::sin(angle - M_PI/2);
    p[3].x = x1 + tk / 2 * std::cos(angle + M_PI/2);
    p[3].y = y1 + tk / 2 * std::sin(angle + M_PI/2);
    thickness_ = 1;
    fill_polygon(p);
    thickness_ = tk;
  }

  std::pair<bool, IVector> Canvas::line_intersects_(double l1p0x, double l1p0y,
                                                    double l1p1x, double l1p1y,
                                                    double l2p0x, double l2p0y,
                                                    double l2p1x, double l2p1y)
  {
    double s1x = l1p1x - l1p0x;
    double s1y = l1p1y - l1p0y;
    double s2x = l2p1x - l2p0x;
    double s2y = l2p1y - l2p0y;
    double det = -s2x * s1y + s1x * s2y;

    double s = (-s1y * (l1p0x - l2p0x) + s1x * (l1p0y - l2p0y)) / det;
    double t = ( s2x * (l1p0y - l2p0y) - s2y * (l1p0x - l2p0x)) / det;

    return {s >= 0 && s <= 1 && t >= 0 && t <= 1,
        IVector(l1p0x + t * s1x, l1p0y + t * s1y)}; 
  }

}
