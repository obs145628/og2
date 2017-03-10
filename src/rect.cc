#include "rect.hh"

namespace og2
{

  IRect irect_unbox(const SDL_Rect& rect)
  {
    return IRect(rect.x, rect.y, rect.w, rect.h);
  }
  
  SDL_Rect irect_box(const IRect& rect)
  {
    SDL_Rect res;
    res.x = rect.x;
    res.y = rect.y;
    res.w = rect.w;
    res.h = rect.h;
    return res;
  }
  
}
