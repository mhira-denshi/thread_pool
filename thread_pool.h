#include "stdint.h"

typedef void(*task_ptr_t)(void*);

typedef struct thread_pool_task {
    task_ptr_t task_ptr;
    void* args;
}thread_pool_task_t;

void schedule_init(int numThreads);

void schedule(task_ptr_t task_func, void* task_args);

void schedule_deinit();