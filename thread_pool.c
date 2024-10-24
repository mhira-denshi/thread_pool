#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "thread_pool.h"
#include "thread_queue.h"

static pthread_t* workers_thread = NULL;
static uint8_t numThreads = 0;
static thread_queue_t thread_queue = {0};
static uint8_t threadPoolStoped = 0;

static pthread_mutex_t thread_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t thread_threadPoolStoped_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t thread_queue_cond = PTHREAD_COND_INITIALIZER;

void* worker() {
    thread_pool_task_t *thread_pool_task = NULL;

    pthread_mutex_lock(&thread_queue_mutex);
    while(1) {
        if(isThreadPoolEmpty(&thread_queue)) {

            pthread_mutex_lock(&thread_threadPoolStoped_mutex);
            if(threadPoolStoped) {
                pthread_mutex_unlock(&thread_queue_mutex);
                pthread_mutex_unlock(&thread_threadPoolStoped_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&thread_threadPoolStoped_mutex);

            pthread_cond_wait(&thread_queue_cond, &thread_queue_mutex);
            continue;
        }

        thread_pool_task = thread_dequeue(&thread_queue);
        pthread_mutex_unlock(&thread_queue_mutex);

        thread_pool_task->task_ptr(thread_pool_task->args);
        free(thread_pool_task);
    }
}

void schedule_init(int numThread)
{
    numThreads = numThread;
    workers_thread = malloc(sizeof(pthread_t) * numThread);

    for(int i=0; i < numThreads; i++) {
        pthread_create(&workers_thread[i], NULL, worker, NULL);
    }

}

void schedule(task_ptr_t task_func, void* task_args)
{
    thread_pool_task_t* thread_pool_task = (thread_pool_task_t*)malloc(sizeof(thread_pool_task_t));

    thread_pool_task->task_ptr = task_func;
    thread_pool_task->args = task_args;

    pthread_mutex_lock(&thread_queue_mutex);

    thread_enqueue(&thread_queue, thread_pool_task);

    pthread_mutex_unlock(&thread_queue_mutex);

    pthread_cond_signal(&thread_queue_cond);

}

void schedule_deinit()
{
    pthread_mutex_lock(&thread_threadPoolStoped_mutex);
    threadPoolStoped = 1;
    pthread_mutex_unlock(&thread_threadPoolStoped_mutex);

    pthread_cond_broadcast(&thread_queue_cond);
    for(int i=0; i<numThreads; i++) {
        pthread_join(workers_thread[i], NULL);
    }

    free(workers_thread);
}
