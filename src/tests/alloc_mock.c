#include "alloc_mock.h"

volatile int s21_calloc_mock_active = 0;
volatile int s21_calloc_mock_fail_at = 1;
volatile int s21_calloc_call_count = 0;

#ifdef __APPLE__
#include <malloc/malloc.h>
#include <stdlib.h>

static void* mocked_calloc(size_t count, size_t size) {
  if (s21_calloc_mock_active) {
    s21_calloc_call_count++;
    if (s21_calloc_call_count >= s21_calloc_mock_fail_at) return NULL;
  }
  return malloc_zone_calloc(malloc_default_zone(), count, size);
}

typedef struct {
  void* new_func;
  void* orig_func;
} interpose_t;

__attribute__((used, section("__DATA,__interpose"))) static const interpose_t
    s21_calloc_interpose = {(void*)mocked_calloc, (void*)calloc};

#else
#include <stddef.h>

void* __real_calloc(size_t count, size_t size);

void* __wrap_calloc(size_t count, size_t size) {
  if (s21_calloc_mock_active) {
    s21_calloc_call_count++;
    if (s21_calloc_call_count >= s21_calloc_mock_fail_at) return NULL;
  }
  return __real_calloc(count, size);
}

#endif
