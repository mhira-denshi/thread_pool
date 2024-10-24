#include "thread_pool.h"
#include <stdlib.h>

#include "thread_queue.h"


thread_queue_node_t* create_thread_queue_node(thread_pool_task_t* thread_pool_task)
{
    thread_queue_node_t* temp = (thread_queue_node_t*)malloc(sizeof(thread_queue_node_t));

    temp->next = NULL;
    temp->thread_pool_task = thread_pool_task;

    return temp;
}


void thread_enqueue(thread_queue_t* thread_queue, thread_pool_task_t* thread_pool_task)
{
    thread_queue_node_t* new = create_thread_queue_node(thread_pool_task);

    if( (thread_queue->front == NULL) && (thread_queue->rear == NULL) ){
        thread_queue->front = thread_queue->rear = new;
        return;
    }

    thread_queue->rear->next = new;
    thread_queue->rear = new;
}

thread_pool_task_t* thread_dequeue(thread_queue_t* thread_queue)
{
    if(thread_queue->front == NULL) {
        return NULL;
    }

    thread_queue_node_t* front = thread_queue->front;

    thread_pool_task_t* val = front->thread_pool_task;

    thread_queue->front = thread_queue->front->next;

    if(thread_queue->front == NULL) {
        thread_queue->rear = NULL;
    }

    free(front);

    return val;
}

uint8_t isThreadPoolEmpty(thread_queue_t* thread_queue)
{
    return thread_queue->front == NULL;
}
