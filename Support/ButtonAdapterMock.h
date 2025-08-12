#ifndef BUTTONADAPTERMOCK_H
#define BUTTONADAPTERMOCK_H

#include <ButtonAdapterInterface.h>

#include <gmock/gmock.h>

class ButtonAdapterMock : public ButtonAdapterInterface
{
public:
  MOCK_METHOD(bool, Begin, (), (override));

  MOCK_METHOD(PanelState, GetPanelState, (), (const override));
  MOCK_METHOD(void, SetButtonAdapterState, (const PanelState), (override));

  MOCK_METHOD(void, SetLEDState, (const bool), (override));
};

#endif
