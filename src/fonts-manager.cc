#include "fonts-manager.hh"
#include <cstdlib>
#include <iostream>
#include "app.hh"
#include "path.hh"

namespace og2
{

  FontsManager& FontsManager::instance()
  {
    static FontsManager res;
    return res;
  }

  TTF_Font* FontsManager::load(const char* path, int size)
  {
    Key key;
    key.path = path;
    key.size = size;
    auto it = fonts_.find(key);
    if (it != fonts_.end())
      return it->second;

    auto tpath = Path::join(App::ressources_root_get(), path);
    auto font = TTF_OpenFont(tpath.c_str(), size);
    if (!font)
      {
        std::cerr << "Error: Cannot open font " << path << ": "
                  << TTF_GetError() << "\n";
        exit(1);
      }

    #ifndef NDEBUG
    std::cerr << "Debug: Load font " << path << " (" << size <<  "pt)\n"; 
    #endif

    fonts_[key] = font;
    return font;
	}


  FontsManager::~FontsManager()
  {
    for (auto it : fonts_)
      TTF_CloseFont(it.second);
  }



}
