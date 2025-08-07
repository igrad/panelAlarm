#ifndef DISPLAYINTERFACE_H
#define DISPLAYINTERFACE_H

#include "Constants.h"

template<typename Serial>
class DisplayCommsInterface {
public:
  virtual DisplayCommsInterface* GetDisplayComms(Serial serialInterface) = 0;

  virtual void SendAlarmCode(const AlarmCode code) = 0;
  virtual Command GetCurrentCommand() = 0;
};

#endif
