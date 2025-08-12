cmake_minimum_required(VERSION 3.28)
project(PanelAlarm LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing(true)

include_directories(
    Button
    Common
    Display
    Logger
    Support
    SystemHarnesses
    Timer
    ThirdParty
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES
    Button/ButtonAdapterInterface.h
    Button/ButtonManager.cpp
    Button/ButtonManager.h
    Button/ButtonManagerInterface.h

    Common/CommonTypes.cpp
    Common/CommonTypes.h
    Common/Constants.h
    Common/Definitions.h
    Common/TimeHelpers.h

    Display/DisplayAdapterInterface.h
    Display/DisplayManager.cpp
    Display/DisplayManager.h

    Logger/DebugLogger.cpp
    Logger/DebugLogger.h
    Logger/LoggerHelpers.h
    Logger/SystemLogger.cpp
    Logger/SystemLogger.h

    Timer/Timer.cpp
    Timer/Timer.h

    SystemHarnesses/SystemHarnessInterface.h
    SystemHarnesses/SystemTestHarness.h
)

set(TEST_SOURCES
    Support/ButtonAdapterMock.h
    Support/ButtonManagerMock.h
    Support/DisplayAdapterMock.h
    Support/LoggerFake.h
)

add_executable(PanelAlarm ${PROJECT_SOURCES} ${TEST_SOURCES})
target_link_libraries(
    PanelAlarm
	GTest::gtest_main
	GTest::gmock
)
target_compile_options(PanelAlarm PRIVATE -Wall -Wextra)

include(GoogleTest)
gtest_discover_tests(PanelAlarm)
