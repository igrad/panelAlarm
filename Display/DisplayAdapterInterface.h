#ifndef DISPLAYADAPTERINTERFACE_H
#define DISPLAYADAPTERINTERFACE_H

#include <CommonTypes.h>

class DisplayAdapterInterface
{
public:
  virtual Command GetCommand() const = 0;
  virtual void SendAlarmCode(AlarmCode code) = 0;
};

#endif
