#include "CommonTypes.h"

#include <map>

std::string ToString(Command cmd)
{
  static std::map<Command, std::string> map = {
    { Command::None, "None" },
    { Command::Arm, "Arm" },
    { Command::Disarm, "Disarm" },
    { Command::AckSecured, "AckSecured" },
    { Command::AckUnsecured, "AckUnsecured" },
    { Command::Unknown, "Unknown" }
  };

  return map[cmd];
}
