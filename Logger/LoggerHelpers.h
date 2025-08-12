#ifndef LOGGERHELPERS_H
#define LOGGERHELPERS_H

#include <TimeHelpers.h>

#include <sstream>

namespace LoggerHelpers
{
  inline void ProcessArgs(std::stringstream&)
  {
  }

  template<typename T, typename... Args>
  inline void ProcessArgs(std::stringstream& sstream, const T& arg, const Args&... args)
  {
    sstream << arg;
    LoggerHelpers::ProcessArgs(sstream, args...);
  }

  template<typename... Args>
  std::string GetStringFromArgs(const Args&... args) {
    std::stringstream out;
    LoggerHelpers::ProcessArgs(out, TimeHelpers::GetTimeSinceEpoch(), ": ", args...);
    return out.str();
  }
}

#endif
