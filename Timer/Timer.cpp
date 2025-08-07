#include "Timer.h"

#include <Arduino.h>
#include <algorithm>

std::vector<Timer*> Timer::AllTimers;

void Timer::UpdateTimers(const unsigned long timestamp)
{
  // Timers are updated by order of registration
  for (Timer* timer : Timer::AllTimers)
  {
    timer->Update(timestamp);
  }
}

Timer::Timer(
  const unsigned long duration,
  std::function<void()> callback,
  const bool singleShot)
  : Callback(callback)
  , StartTime(0)
  , Duration(duration)
  , RemainingDuration(Duration)
  , LastUpdateTimestamp(0)
  , Paused(true)
  , Started(false)
  , SingleShot(singleShot)
{
}

Timer::~Timer()
{
  // If UpdateTimers is not called before this is scheduled for deletion, the final callback
  // trigger may not fire. Probably never going to be a problem though.
  const auto iter = std::find(AllTimers.begin(), AllTimers.end(), *this);

  if (AllTimers.end() != iter)
  {
    AllTimers.erase(iter);
  }
}

bool Timer::IsStarted() const
{
  return Started;
}

bool Timer::IsPaused() const
{
  return Paused;
}

unsigned long Timer::GetElapsedTime() const
{
  return LastUpdateTimestamp;
}

void Timer::Start()
{
  if (!Started)
  {
    Started = true;
    Paused = false;
    RemainingDuration = Duration;
    StartTime = millis();
  }
}

void Timer::Restart()
{
  Stop();
  Start();
}

void Timer::Stop()
{
  if (Started)
  {
    Started = false;
  }
}

void Timer::Pause()
{
  if (!Paused && Started)
  {
    RemainingDuration = millis() - StartTime;
    Paused = true;
  }
}

void Timer::Resume()
{
  if (Paused && Started)
  {
    StartTime = millis() - RemainingDuration;
    Paused = false;
  }
}

void Timer::Update(const unsigned long currentTime)
{
  if (!Paused && Started)
  {
    const unsigned long elapsedTime = currentTime - StartTime;

    if (elapsedTime >= Duration)
    {
      Callback();

      if (!SingleShot)
      {
        Restart();
      }
      else
      {
        Stop();
      }
    }

    LastUpdateTimestamp = currentTime;
  }
}
