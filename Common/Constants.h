#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

// Do this to prevent type mismatching/buffer undersizing later in code
typedef uint8_t BufferSizeType;


constexpr BufferSizeType BUFFER_SIZE = 100;       //command buffer size constexpr uint16_t MAX_RETRIES = 500;      //maximum number of state alerts. not currently implemented
constexpr uint16_t ACK_TIMEOUT_MS = 5000;  //time between alert spamming. not currently implemented
constexpr uint16_t DEBOUNCE = 1000;        //button debounce time. not currenlty implemented
constexpr uint32_t BAUD_RATE = 115200;     //uart comms baud rate

constexpr char PANEL_SECURED_CODE = ']';
constexpr char PANEL_UNSECURED_CODE = '[';

constexpr uint32_t SPAM_PERIOD_MS = 100;
constexpr uint32_t COMMAND_CHECK_PERIOD_MS = 100;
constexpr uint32_t BUTTON_CHECK_PERIOD_MS = 100;

#endif
