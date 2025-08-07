#include "Logger.h"
#include "Definitions.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

#ifndef TESTING
#include <Arduino.h>
#endif

namespace {
  // TODO: Implement rotating log file
  // TODO: Check for available disk space before logging, never exceed more than some set amount.
  // Need to define what device this is actually running on before committing to a max amount.
  constexpr const char LOG_FILE_LOCATION[] = "/var/log/panelAlarm/panelAlarm.log";

  unsigned long long GetTimeSinceEpoch() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count();
  }

  void ProcessArgs(std::stringstream&) {
  }

  template<typename T, typename... Args>
  void ProcessArgs(std::stringstream& sstream, const T& arg, const Args&... args) {
    sstream << arg;
    ProcessArgs(sstream, args...);
  }

  template<typename... Args>
  std::string FormatString(const Args&... args) {
    std::stringstream sstream;
    ProcessArgs(sstream, args...);
    return sstream.str();
  }

  template<typename... Args>
  std::string GetStringFromArgs(const Args&... args) {
    std::stringstream out;
    ProcessArgs(out, GetTimeSinceEpoch(), ": ", args...);
    return out.str();
  }
}

Logger* Logger::TheLogger = nullptr;

Logger* Logger::GetLogger() {
  if (nullptr == Logger::TheLogger) {
    Logger::TheLogger = new Logger();
  }
  return Logger::TheLogger;
}

Logger::~Logger() {
  if (nullptr != Logger::TheLogger) {
    delete Logger::TheLogger;
    Logger::TheLogger = nullptr;
  }
}

template<typename... Args>
void Logger::Debug(const Args&... args) {
  #if defined(TESTING)
  std::cout << GetStringFromArgs(args...);
  #elif defined(DEBUG)
  Serial.print(GetStringFromArgs(args...));
  #endif

  #if defined(LOG_TO_FILE)
  LogToDebugFile(GetStringFromArgs(args...));
  #endif
}

template<typename... Args>
void Logger::DebugLn(const Args&... args) {
  #if defined(TESTING)
  std::cout << GetStringFromArgs(args...) << "\n";
  #elif defined(DEBUG)
  Serial.println(GetStringFromArgs(args...));
  #endif

  #if defined(LOG_TO_FILE)
  LogToDebugFile(GetStringFromArgs(args...));
  #endif
}

void Logger::LogToDebugFile(const std::string& str) {
  // Check if there's enough space on disk
  // Check if we need to rotate logs
  // Log out
  std::ofstream outputFile(LOG_FILE_LOCATION);

  if (outputFile.is_open()) {
    outputFile << str;

    outputFile.close();
  }
  else {
    #undef LOG_TO_FILE
    DebugLn("ERROR: Unable to open log file: ", LOG_FILE_LOCATION);
  }
}
