#ifndef SYSTEMLOGGER_H
#define SYSTEMLOGGER_H

#include "LoggerHelpers.h"

#include <TimeHelpers.h>

#include <iostream>
#include <stdarg.h>
#include <string>

class SystemLogger {
public:
  SystemLogger* GetLogger();

  template<typename... Args>
  void LogInfo(const Args&... args)
  {
    Log("INFO", args...);
  }

  template<typename... Args>
  void LogWarning(const Args&... args)
  {
    Log("WARN", args...);
  }

  template<typename... Args>
  void LogError(const Args&... args)
  {
    Log("ERR ", args...);
  }

private:
  SystemLogger();
  SystemLogger(const SystemLogger&) = delete;
  SystemLogger& operator=(const SystemLogger&) = delete;
  ~SystemLogger();

  template<typename... Args>
  void Log(const std::string& levelStr, const Args&... args)
  {
    const std::string str = LoggerHelpers::GetStringFromArgs(TimeHelpers::GetTimeSinceEpoch(),
                                                             levelStr,
                                                             args...);

    #if defined(TESTING)
    std::cout << str;
    #elif defined(DEBUG)
    Serial.print(str);
    #endif

    LogToSystemFile(str);
  }

  void LogToSystemFile(const std::string& str);

  static SystemLogger* TheLogger;
};

#endif
