#include <ButtonManager.h>

#include <ButtonAdapterMock.h>
#include <Constants.h>
#include <DebugLogger.h>
#include <DisplayManagerMock.h>
#include <SystemLogger.h>
#include <Timer.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

class ButtonManagerTest: public Test
{
public:
  ButtonManagerTest()
    : ButtonAdapter()
    , SysLogger(*SystemLogger::GetLogger())
    , DbgLogger(*DebugLogger::GetLogger())
    , DisplayManager()
    , BtnManager(ButtonAdapter, SysLogger, DbgLogger)
  {
  }

  void SetDisplayManager()
  {
    BtnManager.SetDisplayManagerInterface(&DisplayManager);
  }

  NiceMock<ButtonAdapterMock> ButtonAdapter;
  SystemLogger& SysLogger;
  DebugLogger& DbgLogger;
  NiceMock<DisplayManagerMock> DisplayManager;

  // Friendly class accessors
  ButtonManager BtnManager;
};

TEST_F(ButtonManagerTest, WhenConstructedThenConfigureStateCheckTimer)
{
