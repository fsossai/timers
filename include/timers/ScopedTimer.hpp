#ifndef SCOPED_TIMER_HPP
#define SCOPED_TIMER_HPP

#include <string>

#include "Stopwatch.hpp"
#include "scoped_timer.h"

class ScopedTimer {
public:
  explicit ScopedTimer(const char *name) noexcept {
    scoped_timer_start(&st, name);
  }

  explicit ScopedTimer(Stopwatch &stopwatch) noexcept : sw(&stopwatch) {
    sw->start();
  }

  ~ScopedTimer() noexcept {
    if (sw != nullptr) {
      sw->stop();
    } else {
      scoped_timer_stop(&st);
    }
  }

private:
  scoped_timer_t st;
  Stopwatch *sw = nullptr;
};

#endif // SCOPED_TIMER_HPP
