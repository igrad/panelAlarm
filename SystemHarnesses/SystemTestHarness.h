#ifndef SYSTEMTESTHARNESS_H
#define SYSTEMTESTHARNESS_H

#include "../SystemHarnessInterface.h"

// Replaces the Arduino sketch environment to simulate system-level tests
class SystemTestHarness final : public SystemHarnessInterface {
public:
  SystemTestHarness();
  ~SystemTestHarness() = default;

  void setup() override;
  void loop() override;

private:
  Logger* logger;
};

#endif
