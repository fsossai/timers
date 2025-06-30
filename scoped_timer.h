#ifndef SCOPED_TIMER_H
#define SCOPED_TIMER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  struct timespec start_time;
  const char *name;
  bool active;
} scoped_timer_t;

static inline void scoped_timer_start(scoped_timer_t *st, const char *name) {
  st->name = name;
  st->active = true;
  clock_gettime(CLOCK_MONOTONIC, &st->start_time);
}

static inline void scoped_timer_stop(scoped_timer_t *st) {
  if (!st->active) {
    return;
  }
  struct timespec end;
  clock_gettime(CLOCK_MONOTONIC, &end);
  double elapsed_ms = (end.tv_sec - st->start_time.tv_sec) * 1.0 +
                      (end.tv_nsec - st->start_time.tv_nsec) / 1e9;
  printf("[scoped_timer] %s: %.3f s\n", st->name ? st->name : "(unnamed)",
         elapsed_ms);
  st->active = false;
}

static scoped_timer_t *__scoped_timers[64];
static int __scoped_timer_count = 0;

static inline void TIMER_START(const char *name) {
  scoped_timer_t *st = (scoped_timer_t *)malloc(sizeof(scoped_timer_t));
  scoped_timer_start(st, name);
  __scoped_timers[__scoped_timer_count++] = st;
}

static inline void TIMER_STOP() {
  scoped_timer_t *st = __scoped_timers[--__scoped_timer_count];
  scoped_timer_stop(st);
  free(st);
}

#endif // SCOPED_TIMER_H
