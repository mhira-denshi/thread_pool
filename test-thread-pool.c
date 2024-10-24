#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#include "thread_pool.h"

void example_task(void* args) {
    uint8_t stime = rand()%20;
    sleep(stime);
    printf("example_task : %d\n",stime);
    return;
}

sem_t even;
sem_t odd;

void printEven() {
    for(int i = 0; i < 10; i +=2) {
        sem_wait(&even);
        printf("%d ", i);
        sem_post(&odd);
    }
}

void printOdd() {
    for(int i = 1; i < 10; i +=2) {
        sem_wait(&odd);
        printf("%d ", i);
        sem_post(&even);
    }
}

int common = 1;

sem_t pCommon;
sem_t pSpace;
sem_t iCommon;

void printCommon()
{
    while(common < 100) {
        sem_wait(&pCommon);
        printf("%d", common);
        sem_post(&pSpace);
    }
}

void printSpace()
{
    while(common < 100) {
        sem_wait(&pSpace);
        printf(" ");
        sem_post(&iCommon);
    }
}

void incrementCommon()
{
    while(common < 100) {
        sem_wait(&iCommon);
        common++;
        sem_post(&pCommon);
    }
}

int main()
{
    schedule_init(16);
    sem_init(&pCommon,0 , 1);
    sem_init(&pSpace,0 , 0);
    sem_init(&iCommon,0 , 0);

    schedule(printCommon, NULL);
    schedule(printSpace, NULL);
    schedule(incrementCommon, NULL);

    schedule_deinit();
    printf("\n");
    return 0;
}