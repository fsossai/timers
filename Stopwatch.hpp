#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include "scoped_timer.h"
#include "stopwatch.h"
#include <string>

class Stopwatch {
public:
  explicit Stopwatch(const char *name, bool auto_display = true) noexcept
      : auto_display(auto_display) {
    stopwatch_init(&sw, name);
  }

  ~Stopwatch() {
    if (auto_display) {
      stopwatch_print(&sw);
    }
  }

  void start() noexcept { stopwatch_start(&sw); }
  void stop() noexcept { stopwatch_stop(&sw); }
  void reset() noexcept { stopwatch_reset(&sw); }
  void print() noexcept { stopwatch_print(&sw); }

  double milliseconds() const noexcept { return stopwatch_milliseconds(&sw); }
  double seconds() const noexcept { return stopwatch_seconds(&sw); }
  long laps() const noexcept { return sw.laps; }

  const char *name() const noexcept { return sw.name; }

private:
  stopwatch_t sw;
  bool auto_display;
};

#endif // STOPWATCH_HPP
