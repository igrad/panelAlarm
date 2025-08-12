#ifndef DISPLAYMANAGERINTERFACE_H
#define DISPLAYMANAGERINTERFACE_H

#include <CommonTypes.h>

class DisplayManagerInterface
{
public:
  virtual ~DisplayManagerInterface() = default;

  virtual void SpamAlarmCodeUntilAck(AlarmCode code) = 0;
};

#endif
