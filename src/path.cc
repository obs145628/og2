#include "path.hh"
#include <set>
#include <iostream>

namespace og2
{

  std::string Path::join(const std::string& a, const std::string& b)
  {
    if (a.empty())
      return b;
    if (b.empty())
      return a;

    if (b[0] == '/')
      return b;

    std::string res = a;
    if (res.back() != '/')
      res.push_back('/');
    res += b;
    return res;
  }

  const char* Path::unique(const std::string& path)
  {
    static std::set<std::string> set;
    auto ins = set.insert(path);
    return ins.first->c_str();
  }
  
}
