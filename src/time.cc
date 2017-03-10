#include "time.hh"
#include <chrono>

namespace og2
{
  long Time::now()
  {
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::system_clock;
    return duration_cast<milliseconds>(
      system_clock::now()
      .time_since_epoch()).count();
  }
}
