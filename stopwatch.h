#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

typedef struct {
  struct timespec start_time;
  double elapsed_ms;
  bool running;
  long laps;
  const char *name;
} stopwatch_t;

static inline double stopwatch_timespec_diff_ms(const struct timespec *end,
                                                const struct timespec *start) {
  return (end->tv_sec - start->tv_sec) * 1000.0 +
         (end->tv_nsec - start->tv_nsec) / 1e6;
}

static inline void stopwatch_init(stopwatch_t *sw, const char *name) {
  sw->elapsed_ms = 0.0;
  sw->running = false;
  sw->name = name;
  sw->laps = 0;
}

static inline double stopwatch_milliseconds(const stopwatch_t *sw) {
  return sw->elapsed_ms;
}

static inline double stopwatch_seconds(const stopwatch_t *sw) {
  return stopwatch_milliseconds(sw) / 1000.0;
}

static inline void stopwatch_print(const stopwatch_t *sw) {
  double ms = stopwatch_milliseconds(sw);
  printf("[stopwatch] %s: %.3f ms\n", sw->name, ms);
}

static inline void stopwatch_print_stats(const stopwatch_t *sw) {
  double ms = stopwatch_milliseconds(sw);
  printf("[stopwatch] %s: %.3f ms (avg: %.3f ms, laps: %li)\n", sw->name, ms,
         ms / sw->laps, sw->laps);
}

static inline void stopwatch_start(stopwatch_t *sw) {
  if (!sw->running) {
    clock_gettime(CLOCK_MONOTONIC, &sw->start_time);
    sw->running = true;
  }
}

static inline void stopwatch_stop(stopwatch_t *sw) {
  if (sw->running) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    sw->elapsed_ms += stopwatch_timespec_diff_ms(&now, &sw->start_time);
    sw->running = false;
    ++sw->laps;
  }
}

static inline void stopwatch_reset(stopwatch_t *sw) {
  sw->elapsed_ms = 0.0;
  sw->running = false;
}

#endif // STOPWATCH_H
