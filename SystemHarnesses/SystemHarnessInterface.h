#ifndef SYSTEMHARNESSINTERFACE_H
#define SYSTEMHARNESSINTERFACE_H

// The SystemHarnessInterface acts as the intermediary level between the Arduino sketch (*.ino)
// file or the testing execution executable to abstract away business logic for the desired
// operation. This ensures that what runs on the controller is exactly the same as what run in
// a testing environment. The only difference is the DEBUG or TESTING macros, which should be
// limited to minimal system performance impact.
class SystemHarnessInterface {
public:
  ~SystemHarnessInterface() = default;

  virtual void setup() = 0;
  virtual void loop() = 0;
  virtual void end() = 0;
};

#endif
