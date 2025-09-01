#ifndef DISPLAYADAPTERMOCK_H
#define DISPLAYADAPTERMOCK_H

#include <DisplayAdapterInterface.h>

#include <gmock/gmock.h>

class DisplayAdapterMock: public DisplayAdapterInterface
{
public:
  MOCK_METHOD(Command, GetCommand, (), (const, override));
  MOCK_METHOD(void, SendAlarmCode, (AlarmCode code), (override));
};

#endif
