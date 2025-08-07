/* Simple Timer
   by: Ian Gradert
   date: Aug 3, 2025
   license: MIT License - Feel free to use this code for any purpose.
   This is a very simple single-action timer for use by panelAlarm.ino
*/

#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <vector>

class Timer {
public:
  Timer(const unsigned long duration,
        std::function<void()> callback,
        const bool singleShot = true);
  Timer(const Timer&) = delete;
  Timer operator=(const Timer&) = delete;
  ~Timer();

  static void UpdateTimers(const unsigned long timestamp);

  bool IsStarted() const;
  bool IsPaused() const;
  unsigned long GetElapsedTime() const;

  void Start();
  void Restart();
  void Stop();
  void Pause();
  void Resume();


private:
  static std::vector<Timer*> AllTimers;

  void Update(const unsigned long currentTime);

  std::function<void()> Callback;

  unsigned long StartTime;
  unsigned long Duration;
  unsigned long RemainingDuration;
  unsigned long LastUpdateTimestamp;

  bool Paused;
  bool Started;
  bool SingleShot;
};

#endif
