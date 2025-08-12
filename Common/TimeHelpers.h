#ifndef TIMEHELPERS_H
#define TIMEHELPERS_H

#include <Definitions.h>

#include <chrono>

namespace TimeHelpers
{
  inline unsigned long long GetTimeSinceEpoch()
  {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count();
  }
}
#endif
