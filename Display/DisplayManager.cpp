#include "DisplayManager.h"

#include <ButtonManagerInterface.h>
#include <CommonTypes.h>
#include <Constants.h>
#include <DebugLogger.h>
#include <DisplayAdapter.h>
#include <SystemLogger.h>

DisplayManager::DisplayManager(
  DisplayAdapterInterface& display,
  ButtonManagerInterface& buttonManager,
  SystemLogger& sysLogger,
  DebugLogger& dbgLogger)
  : Display(display)
  , ButtonManager(buttonManager)
  , SysLogger(sysLogger)
  , DbgLogger(dbgLogger)
  , SpamTimer()
  , CommandCheckTimer()
  , ActiveCode(AlarmCode::None)
  , AwaitingCommand(Command::None)
{
  SpamTimer.SetDuration(SPAM_PERIOD_MS);
  SpamTimer.SetSingleShot(false);
  SpamTimer.SetCallback(std::bind(&DisplayManager::Spam, this));

  CommandCheckTimer.SetDuration(COMMAND_CHECK_PERIOD_MS);
  CommandCheckTimer.SetSingleShot(false);
  CommandCheckTimer.SetCallback(std::bind(&DisplayManager::CheckForCommands, this));
}

void DisplayManager::SpamAlarmCodeUntilAck(AlarmCode code)
{
  ActiveCode = code;

  switch(ActiveCode)
  {
    case AlarmCode::None:
    {
      SpamTimer.Stop();
      AwaitingCommand = Command::None;
      break;
    }
    case AlarmCode::Secured:
    {
      SpamTimer.Start();
      AwaitingCommand = Command::AckSecured;
      break;
    }
    case AlarmCode::Unsecured:
    {
      SpamTimer.Start();
      AwaitingCommand = Command::AckUnsecured;
      break;
    }
  }

  Spam();
}

void DisplayManager::Spam()
{
  if(ActiveCode != AlarmCode::None)
  {
    Display.SendAlarmCode(ActiveCode);
  }
}

void DisplayManager::CheckForCommands()
{
  const Command receivedCommand = Display.GetCommand();

  if(Command::None != receivedCommand)
  {
    if(Command::None != AwaitingCommand)
    {
      if(receivedCommand == AwaitingCommand)
      {
        HandleAck();
      }
      else
      {
        DbgLogger.DebugLn("Must ACK before handling ",
                          ToString(receivedCommand),
                          " command");
      }
    }
    else if(Command::Arm == receivedCommand)
    {
      ButtonManager.ArmPanel();
    }
    else if(Command::Disarm == receivedCommand)
    {
      ButtonManager.DisarmPanel();
    }
  }
}

void DisplayManager::HandleAck()
{
  SpamTimer.Stop();
  AwaitingCommand = Command::None;
  ActiveCode = AlarmCode::None;
}
