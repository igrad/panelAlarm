#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

enum class PanelState : int {
  Unsecured = 0,
  Secured
};

enum class AlarmCode : char {
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
  Ack,
  Unknown
};

// Do this to prevent type mismatching/buffer undersizing later in code
typedef uint8_t BufferSizeType;


constexpr BufferSizeType BUFFER_SIZE = 100;       //command buffer size constexpr uint16_t MAX_RETRIES = 500;      //maximum number of state alerts. not currently implemented
constexpr uint16_t ACK_TIMEOUT_MS = 5000;  //time between alert spamming. not currently implemented
constexpr uint16_t DEBOUNCE = 1000;        //button debounce time. not currenlty implemented
constexpr uint32_t BAUD_RATE = 115200;     //uart comms baud rate

#endif
