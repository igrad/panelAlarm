#include "ButtonManager.h"

#include "ButtonAdapterInterface.h"

#include <Constants.h>
#include <DebugLogger.h>
#include <DisplayManagerInterface.h>
#include <SystemLogger.h>

ButtonManager::ButtonManager(
    ButtonAdapterInterface& adapter,
    SystemLogger& sysLogger,
    DebugLogger& dbgLogger)
  : Adapter(adapter)
  , DisplayManager(nullptr)
  , ArmState(AlarmState::Unarmed)
  , SysLogger(sysLogger)
  , DbgLogger(dbgLogger)
  , State(PanelState::Unsecured)
  , StateCheckTimer()
{
  StateCheckTimer.SetDuration(BUTTON_CHECK_PERIOD_MS);
  StateCheckTimer.SetCallback(std::bind(&ButtonManager::CheckState, this));
  StateCheckTimer.SetSingleShot(false);
}

void ButtonManager::SetDisplayManagerInterface(DisplayManagerInterface* displayManager)
{
  DisplayManager = displayManager;
}

void ButtonManager::ConnectToButton()
{
  // If we cannot connect to the button, do not proceed
  bool firstAttemptComplete = false;
  while(!Adapter.Begin())
  {
    if(!firstAttemptComplete)
    {
      // DbgLogger.DebugLn("Failed to connect to button! Attempting reconnect...");
      SysLogger.LogInfo("Failed to connect to button! Attempting reconnect...");
      firstAttemptComplete = true;
    }
  }

  StateCheckTimer.Start();
}

void ButtonManager::ArmPanel()
{
  ArmState = AlarmState::Armed;
  Adapter.SetLEDState(false);
}

void ButtonManager::DisarmPanel()
{
  ArmState = AlarmState::Unarmed;
  Adapter.SetLEDState(true);
}

void ButtonManager::CheckState()
{
  const PanelState state = Adapter.GetPanelState();

  if((ArmState == AlarmState::Armed) && (state != State))
  {
    if(nullptr != DisplayManager)
    {
      if(PanelState::Secured == state)
      {
        DisplayManager->SpamAlarmCodeUntilAck(AlarmCode::Secured);
      }
      else
      {
        DisplayManager->SpamAlarmCodeUntilAck(AlarmCode::Unsecured);
      }
    }
    else
    {
      DbgLogger.DebugLn("ERROR: Failed to connect display to button");
    }

    State = state;
  }
}
