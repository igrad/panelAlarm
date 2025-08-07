cmake_minimum_required(VERSION 3.28)
project(PanelAlarm LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing(true)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES
	 SystemHarnesses/SystemHarness.cpp
	 SystemHarnesses/SystemHarness.h
	 SystemHarnesses/SystemHarnessInterface.h
	 SystemHarnesses/SystemTestHarness.h
	 SystemHarnesses/SystemTestHarness.h
)

set(TEST_SOURCES
    Tests/SystemHarnessTest.cpp
)

add_executable(PanelAlarm ${PROJECT_SOURCES} ${TEST_SOURCES})
target_link_libraries(
    PanelAlarm
	 GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(PanelAlarm)
