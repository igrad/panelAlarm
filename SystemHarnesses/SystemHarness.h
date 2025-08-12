#ifndef SYSTEMHARNESS_H
#define SYSTEMHARNESS_H

#include "SystemHarnessInterface.h"
// #include "Constants.h"
// #include "Definitions.h"
// #include "DisplayInterface.h"
// #include "Logger.h"
// #include "Timer.h"
#include <SparkFun_Qwiic_Button.h>

class SystemHarness : public SystemHarnessInterface {
public:
  SystemHarness();
  ~SystemHarness() = default;

  void setup() override;
  void loop() override;
  void end() override;

private:
  QwiicButton Button;
};

#endif
