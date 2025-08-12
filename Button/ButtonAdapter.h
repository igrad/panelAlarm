#ifndef BUTTONADAPTER_H
#define BUTTONADAPTER_H

#include "ButtonAdapterInterface.h"
#include "../ThirdParty/SparkFun_Qwiic_Button.h"

class ButtonAdapter: public ButtonAdapterInterface
{
public:
  ButtonAdapter();

  bool Begin() override;

  PanelState GetPanelState() const override;

  void SetLEDState(const bool ledOn) override;

private:
  bool GetButtonState() const;

  QwiicButton Button;
};

#endif
