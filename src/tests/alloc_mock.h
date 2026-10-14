#ifndef ALLOC_MOCK_H
#define ALLOC_MOCK_H

extern volatile int s21_calloc_mock_active;
extern volatile int s21_calloc_mock_fail_at;
extern volatile int s21_calloc_call_count;

static inline void s21_enable_calloc_mock(int fail_at_call) {
  s21_calloc_call_count = 0;
  s21_calloc_mock_fail_at = fail_at_call;
  s21_calloc_mock_active = 1;
}

static inline void s21_disable_calloc_mock(void) { s21_calloc_mock_active = 0; }

#endif
