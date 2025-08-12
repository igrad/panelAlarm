#ifndef DISPLAYADAPTER_H
#define DISPLAYADAPTER_H

#include "DisplayAdapterInterface.h"

#include <string>

class DisplayAdapter: public DisplayAdapterInterface
{
public:
  DisplayAdapter();

  void SendAlarmCode(AlarmCode code) override;
  Command GetCommand() const override;

private:
  Command ParseCommandFromString(const std::string& str) const;
};

#endif
