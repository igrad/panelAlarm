#include "SystemLogger.h"

#include <Definitions.h>
#include <TimeHelpers.h>

#include <iostream>
#include <fstream>

namespace {
  // TODO: Implement rotating log file
  // TODO: Check for available disk space before logging, never exceed more than some set amount.
  // Need to define what device this is actually running on before committing to a max amount.
  constexpr const char LOG_FILE_LOCATION[] = "/var/log/panelAlarm/panelAlarm.log";
}

SystemLogger* SystemLogger::TheLogger = nullptr;

SystemLogger* SystemLogger::GetLogger()
{
  if(nullptr == SystemLogger::TheLogger)
  {
    SystemLogger::TheLogger = new SystemLogger();
  }

  return SystemLogger::TheLogger;
}

SystemLogger::SystemLogger()
{
  SystemLogger::TheLogger = this;
}

SystemLogger::~SystemLogger()
{
  if(nullptr != SystemLogger::TheLogger)
  {
    delete SystemLogger::TheLogger;
    SystemLogger::TheLogger = nullptr;
  }
}

void SystemLogger::LogToSystemFile(const std::string& str) {
  // Check if there's enough space on disk
  // Check if we need to rotate logs
  // Log out
  std::ofstream outputFile(LOG_FILE_LOCATION);

  if(outputFile.is_open())
  {
    outputFile << str;

    outputFile.close();
  }
  else
  {
    #undef LOG_TO_FILE
    std::cout << "Unable to open system log file: " << LOG_FILE_LOCATION << std::endl;
  }
}
