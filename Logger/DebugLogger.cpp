#include "DebugLogger.h"
#include "LoggerHelpers.h"

#include <Definitions.h>
#include <TimeHelpers.h>

#include <sstream>

#ifndef TESTING
#include <Arduino.h>
#endif

namespace
{
  template<typename... Args>
  std::string GetStringFromArgs(const Args&... args)
  {
    std::stringstream out;
    LoggerHelpers::ProcessArgs(out, TimeHelpers::GetTimeSinceEpoch(), ": ", args...);
    return out.str();
  }
}

DebugLogger* DebugLogger::TheLogger = nullptr;

DebugLogger* DebugLogger::GetLogger()
{
  if (nullptr == DebugLogger::TheLogger)
  {
    DebugLogger::TheLogger = new DebugLogger();
  }
  return DebugLogger::TheLogger;
}

DebugLogger::DebugLogger()
{
  DebugLogger::TheLogger = this;
}

DebugLogger::~DebugLogger()
{
  if(nullptr != DebugLogger::TheLogger)
  {
    delete DebugLogger::TheLogger;
    DebugLogger::TheLogger = nullptr;
  }
}
