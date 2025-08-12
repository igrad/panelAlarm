#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include "ButtonManagerInterface.h"

#include <CommonTypes.h>
#include <Timer.h>

class ButtonAdapterInterface;
class DebugLogger;
class SystemLogger;

class ButtonManager: public ButtonManagerInterface
{
public:
  ButtonManager(
    ButtonAdapterInterface& adapter,
    SystemLogger& sysLogger,
    DebugLogger& dbgLogger);
  ~ButtonManager() override = default;
  ButtonManager(const ButtonManager&) = delete;
  ButtonManager& operator=(const ButtonManager&) = delete;

  void SetDisplayManagerInterface(DisplayManagerInterface* displayManager) override;
  void ConnectToButton() override;

  void ArmPanel() override;
  void DisarmPanel() override;

private:
  void CheckState();

  ButtonAdapterInterface& Adapter;
  DisplayManagerInterface* DisplayManager;

  AlarmState ArmState;
  SystemLogger& SysLogger;
  DebugLogger& DbgLogger;
  PanelState State;

  Timer StateCheckTimer;
};

#endif
