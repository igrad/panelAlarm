#include "ButtonAdapter.h"

ButtonAdapter::ButtonAdapter()
  : Button()
{

}

bool ButtonAdapter::Begin()
{
  Button.begin();
}

PanelState ButtonAdapter::GetPanelState() const
{
  return Button.isPressed();
}

void ButtonAdapter::SetLEDState(const bool ledOn)
{
  if (ledOn)
  {
    Button.LEDon();
  }
  else
  {
    Button.LEDoff();
  }
}
