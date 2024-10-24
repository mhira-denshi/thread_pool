

typedef struct thread_queue_node {
    struct thread_queue_node* next;

    thread_pool_task_t* thread_pool_task;
}thread_queue_node_t;

typedef struct thread_queue {
    thread_queue_node_t* front;
    thread_queue_node_t* rear;
}thread_queue_t;


void thread_enqueue(thread_queue_t* thread_queue, thread_pool_task_t* thread_pool_task);
thread_pool_task_t* thread_dequeue(thread_queue_t* thread_queue);
uint8_t isThreadPoolEmpty(thread_queue_t* thread_queue);
