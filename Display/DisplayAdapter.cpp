#include "DisplayAdapter.h"

#include <Constants.h>

#include <Arduino.h>

DisplayAdapter::DisplayAdapter()
{
}

void DisplayAdapter::SendAlarmCode(AlarmCode code)
{
  Keyboard.write(ToChar(code));
}

Command DisplayAdapter::GetCommand() const
{
  std::string str;
  char newChar;
  while(Serial.available())
  {
    newChar = Serial.read();

    str.append(1, newChar);
  }

  return ParseCommandFromString(str);
}

Command DisplayAdapter::ParseCommandFromString(const std::string& str) const
{
  Command cmd = Command::None;
  const int length = str.length();
  if((length > 2) &&
     ('<' == str[0]) &&
     ('>' == str[length - 1]))
  {
    if(str.compare("<ARM>") == 0)
    {
      cmd = Command::Arm;
    }
    else if(str.compare("<UNARM>") == 0)
    {
      cmd = Command::Disarm;
    }
    else
    {
      static const std::string securedAckString = std::string("<ACK ")
        .append(1, PANEL_SECURED_CODE)
        .append(1, '>');
      static const std::string unsecuredAckString = std::string("<ACK ")
        .append(1, PANEL_UNSECURED_CODE)
        .append(1, '>');

      if(str.compare(securedAckString) == 0)
      {
        cmd = Command::AckSecured;
      }
      else if(str.compare(unsecuredAckString))
      {
        cmd = Command::AckUnsecured;
      }
      else
      {
        cmd = Command::Unknown;
      }
    }
  }

  return cmd;
}
