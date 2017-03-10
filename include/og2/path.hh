#pragma once

#include <string>

namespace og2
{

  class Path
  {
  public:

    static std::string join(const std::string& a, const std::string& b);

    static const char* unique(const std::string& path);
    
  };
  
}
