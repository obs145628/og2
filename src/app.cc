#include "app.hh"
#include <iostream>
#include <cstdlib>
#include "sdl.hh"

namespace og2
{

  const int App::IMG_FLAGS = IMG_INIT_PNG | IMG_INIT_JPG;

  std::string App::ressources_root_ = ".";

  void App::init()
  {
    static bool init = false;
    if (init)
      return;


    if (SDL_Init(SDL_INIT_VIDEO) < 0)
      {
        std::cerr << "Error: SDL_Init:"
                  << SDL_GetError() << "\n";
        exit(1);
      }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
      std::cerr << "Warning: Linear texture filtering not enabled!\n";

    if (!(IMG_Init(IMG_FLAGS) & IMG_FLAGS))
      {
        std::cerr << "Error: IMG_Init: "
          << IMG_GetError() << "\n";
           exit(1);
			}

    if( TTF_Init() == -1 )
      {
        std::cerr << "Error: TTF_INIT:"
                  << TTF_GetError() << "\n";
        exit(1);
      }


    init = true;
  }

  void App::quit()
  {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
  }

  const std::string& App::ressources_root_get()
  {
    return ressources_root_;
  }
  
  void App::ressources_root_set(const std::string& path)
  {
    ressources_root_ = path;
  }

  IVector App::screen_size_get()
  {
    App::init();
    SDL_DisplayMode mode;
    if (SDL_GetCurrentDisplayMode(0, &mode) < 0)
      {
        std::cerr << "Error: cannot get screen size\n";
        exit(1);
      }
      
    return IVector{mode.w, mode.h};
  }
  
}
