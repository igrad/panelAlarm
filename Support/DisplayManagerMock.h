#ifndef DISPLAYMANAGERMOCK_H
#define DISPLAYMANAGERMOCK_H

#include <DisplayManagerInterface.h>

#include <gmock/gmock.h>

class DisplayManagerMock: public DisplayManagerInterface
{
public:
  MOCK_METHOD(void, SpamAlarmCodeUntilAck, (AlarmCode), (override));
};

#endif
