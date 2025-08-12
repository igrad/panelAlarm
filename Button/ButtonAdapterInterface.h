#ifndef BUTTONADAPTERINTERFACE_H
#define BUTTONADAPTERINTERFACE_H

#include <CommonTypes.h>

class ButtonAdapterInterface
{
public:
  virtual ~ButtonAdapterInterface() = default;

  virtual bool Begin() = 0;

  virtual PanelState GetPanelState() const = 0;

  virtual void SetLEDState(const bool ledOn) = 0;
};

#endif
