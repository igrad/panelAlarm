#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <string>

enum class PanelState : int {
  Unsecured = 0,
  Secured
};

enum class AlarmCode : char {
  None = '\0',
  Unsecured = '[',
  Secured = ']'
};
constexpr char ToChar(const AlarmCode code) {
    return static_cast<char>(code);
}

enum class AlarmState : int {
  Unarmed = 0,
  Armed
};

// Types of commands that can be received
enum class Command : int {
  None = 0,
  Arm,
  Disarm,
  AckSecured,
  AckUnsecured,
  Unknown
};
std::string ToString(Command cmd);

#endif
