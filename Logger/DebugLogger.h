#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H

#include "LoggerHelpers.h"

#include <Definitions.h>

#include <iostream>
#include <stdarg.h>

class DebugLogger
{
public:
  static DebugLogger* GetLogger();

  template<typename... Args>
  void Debug(const Args&... args)
  {
    #if defined(TESTING)
    std::cout << LoggerHelpers::GetStringFromArgs(args...);
    #elif defined(DEBUG)
    Serial.print(GetStringFromArgs(args...));
    #endif
  }

  template<typename... Args>
  void DebugLn(const Args&... args)
  {
    #if defined(TESTING)
    std::cout << LoggerHelpers::GetStringFromArgs(args...) << "\n";
    #elif defined(DEBUG)
    Serial.println(GetStringFromArgs(args...));
    #endif
  }

private:
  DebugLogger();
  DebugLogger(const DebugLogger&) = delete;
  DebugLogger& operator=(const DebugLogger&) = delete;
  ~DebugLogger();

  static DebugLogger* TheLogger;
};

#endif
