#ifndef BUTTONMANAGERINTERFACE_H
#define BUTTONMANAGERINTERFACE_H

class DisplayManagerInterface;

class ButtonManagerInterface
{
public:
  virtual ~ButtonManagerInterface() = default;

  virtual void SetDisplayManagerInterface(DisplayManagerInterface* displayManager) = 0;
  virtual void ConnectToButton() = 0;

  virtual void ArmPanel() = 0;
  virtual void DisarmPanel() = 0;
};

#endif
