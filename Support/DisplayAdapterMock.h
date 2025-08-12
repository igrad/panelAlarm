#ifndef DISPLAYADAPTERMOCK_H
#define DISPLAYADAPTERMOCK_H

#include <DisplayAdapterInterface.h>

#include <gmock/gmock.h>

class DisplayAdapterMock: public DisplayAdapterInterface
{
public:
  MOCK_METHOD(void, SendAlarmCode, (AlarmCode code), (override));
  MOCK_METHOD(Command, GetCommand, (), (const, override));
};

#endif
