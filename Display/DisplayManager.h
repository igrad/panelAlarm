#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "DisplayManagerInterface.h"

#include <Timer.h>

class ButtonManagerInterface;
class DebugLogger;
class DisplayAdapterInterface;
class SystemLogger;

class DisplayManager: public DisplayManagerInterface
{
public:
  DisplayManager(DisplayAdapterInterface& Display,
                 ButtonManagerInterface& ButtonManager,
                 SystemLogger& sysLogger,
                 DebugLogger& dbgLogger);

  void SpamAlarmCodeUntilAck(AlarmCode code) override;

private:
  void Spam();
  void CheckForCommands();
  void HandleAck();

  DisplayAdapterInterface& Display;
  ButtonManagerInterface& ButtonManager;
  SystemLogger& SysLogger;
  DebugLogger& DbgLogger;

  Timer SpamTimer;
  Timer CommandCheckTimer;
  AlarmCode ActiveCode;
  Command AwaitingCommand;
};

#endif
