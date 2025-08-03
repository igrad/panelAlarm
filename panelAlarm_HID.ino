/* HID / TTY Panel Alarm
   by: Jesse DeWald
   Company: VotingWorks
   date: 11/14/2023
   license: MIT License - Feel free to use this code for any purpose.
   This code checks the state of an i2c button (at a default address)
   It sends the state to a host via an HID emulation
   and waits for acknowledgements and commands on UART
*/

#include <Keyboard.h>
#include <SparkFun_Qwiic_Button.h>

#define DEBUG true

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

enum class PanelState : int {
  Unsecured = 0,
  Secured
};

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
// enum PanelState { SECURED,
//                   UNSECURED };  // States of the panel
// enum AlarmState { ARMED,
//                   UNARMED };  // States of the alarm
// enum Command { CMD_NONE,
//                CMD_ARM,
//                CMD_UNARM,
//                CMD_ACK,
//                CMD_UNKNOWN };  // Types of commands that can be received

// Do this to prevent type mismatching/buffer undersizing later in code
typedef uint8_t = BufferSizeType;

namespace {
  constexpr BufferSizeType BUFFER_SIZE = 100;       //command buffer size
  constexpr uint16_t MAX_RETRIES = 500;      //maximum number of state alerts. not currently implemented
  constexpr uint16_t ACK_TIMEOUT_MS = 5000;  //time between alert spamming. not currently implemented
  constexpr uint16_t DEBOUNCE = 1000;        //button debounce time. not currenlty implemented
  constexpr uint32_t BAUD_RATE = 115200;     //uart comms baud rate

  constexpr char PANEL_SECURED_CODE = ']';
  constexpr char PANEL_UNSECURED_CODE = '[';

  QwiicButton panelSwitch;     // The Qwiic Button
  AlarmState alarmState;     // State of the alarm
  char txBuffer[BUFFER_SIZE];  // Buffer for serial communication
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Keyboard.begin();        // Start keyboard HID emulation
  Wire.begin();            // Start I2C communication
  Serial.begin(BAUD_RATE); // Start serial communication at baud rate
  delay(1000);             // Delay to stabilize I2C communication

  // Check if the Qwiic Button is connected and initialized properly
  if (!panelSwitch.begin()) {
    DEBUG_PRINTLN("ERROR: ALARM FAILED TO INITIALIZE");  // Print error message if initialization fails
    while (true) {}                                      // Infinite loop to stop further execution
  }

  DEBUG_PRINTLN("STATUS: ALARM READY");  // Print status message when ready
  alarmState = AlarmState::Disarmed;   // Initialize alarm state
  delay(100);                            // Short delay after setup
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  waitForArmCommand();

  const PanelState panelState = getPanelState();
  char alert;

  switch (panelState) {
    case SECURED:
      DEBUG_PRINTLN("ARMED: PANEL IS SECURED");

      alert = PANEL_SECURED_CODE;
      panelSwitch.LEDoff();
      break;
    case UNSECURED:
      DEBUG_PRINTLN("ARMED: PANEL IS UNSECURED");

      alert = PANEL_UNSECURED_CODE;
      panelSwitch.LEDon();
      break;
  }

  spamAndAck(alert);

  while (getPanelState() == panelState) {
    if (Serial.available()) {
      const Command newCommand = waitForCommand();
      if (Command::Disarm == newCommand) {
        alarmState = AlarmState::Disarmed;
        break;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void waitForArmCommand() {
  // Check if the alarm is unarmed and wait for an ARM command
  if (AlarmState::Disarmed == alarmState) {
    DEBUG_PRINTLN("UNARMED: WAITING FOR ARM COMMAND");

    while (waitForCommand() != Command::Arm);
    alarmState = AlarmState::Armed;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Command waitForCommand() {
  // Function to wait for a command from serial input
  while (!Serial.available());

  getTX();
  Command parsed = parseTX();
  resetBuffer();

  return parsed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void spamAndAck(const char alert) {
  do {
    Keyboard.write(alert);
    delay(ACK_TIMEOUT_MS);
  } while (!Serial.available());

  getTX();

  if (Command::Ack == parseTX()) {
    const int length = strlen(txBuffer);
    const char ackResponse = txBuffer[5];

    if (ackResponse != alert) {
      DEBUG_PRINTLN("WRONG ACK");
      spamAndAck(alert);
    }
  }
  else {
    DEBUG_PRINTLN("NEED TO ACK FIRST");
    spamAndAck(alert);
  }
  resetBuffer();

  DEBUG_PRINTLN("ALERT ACKNOWLEDGED");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void resetBuffer() {
  // Function to reset the transmission buffer
  memset(txBuffer, '\0', BUFFER_SIZE);  // Clear the buffer by setting all values to null character
}

////////////////////////////////////////////////////////////////////////////////////////////////////
PanelState getPanelState() {
  delay(20);  // Short delay for debounce

  if (panelSwitch.isPressed()) {
    return PanelState::Secured;
  }
  else {
    return PanelState::Unsecured;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
char* getTX() {
  BufferSizeType bufferIndex = 0;
  char newChar;

  while (Serial.available()) {
    newChar = Serial.read();

    // Size - 2 so that we can also append terminating char
    // No command should ever get anywhere near this size
    if (bufferIndex < BUFFER_SIZE - 2) {
      txBuffer[bufferIndex] = newChar;
      ++bufferIndex;
    } else {
      break;
    }
    delay(1);  // Short delay for buffer processing
  }

  txBuffer[bufferIndex] = '\0';
  DEBUG_PRINTLN(txBuffer);

  return txBuffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Command parseTX() {
  // Function to parse the transmitted data and extract command
  // Check if the data is enclosed in '<' and '>'
  const BufferSizeType length = strlen(txBuffer);

  Command receivedCommand = Command::None;
  if (length >= 3)
  {
    char message[length - 1];  // Buffer to store the actual message excluding '<' and '>'

    if ((length > 2) &&
        ('<' == txBuffer[0]) &&
        ('>' == txBuffer[length - 1])) {
      strncpy(message, txBuffer + 1, length - 2);  // Copy the message to buffer
      message[length - 2] = '\0';                   // Null-terminate the message

      // Compare the message with predefined commands and return the corresponding enum value
      if (strcmp(message, "ARM") == 0) {
        DEBUG_PRINTLN("ARM command received.");
        receivedCommand = Command::Arm;
      } else if (strcmp(message, "UNARM") == 0) {
        DEBUG_PRINTLN("UNARM command received.");
        receivedCommand = Command::Disarm;
      } else if (strncmp(message, "ACK", 3) == 0) {
        DEBUG_PRINTLN("ACK command received.");
        receivedCommand = Command::Ack;
      } else {
        DEBUG_PRINT("Unknown command: ");
        DEBUG_PRINTLN(message);
        receivedCommand = Command::Unknown;
      }
    } else {
      DEBUG_PRINTLN("No valid message found.");
    }
  }
  else {
    DEBUG_PRINT("Invalid message in transaction buffer, unable to parse command ");
    DEBUG_PRINTLN(txBuffer);
  }

  return receivedCommand;
}
