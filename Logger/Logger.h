#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include <string>

class Logger {
public:
  Logger* GetLogger();

  template<typename... Args>
  void Debug(const Args&...);

  template<typename... Args>
  void DebugLn(const Args&...);

private:
  Logger();
  Logger& operator=(const Logger&) = delete;
  Logger(const Logger&) = delete;
  ~Logger();

  void LogToDebugFile(const std::string& str);

  static Logger* TheLogger;
};

#endif
