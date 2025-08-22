#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} semaphore;

void semaphore_init(semaphore* s, int initial_count);
void semaphore_wait(semaphore* s);
void semaphore_signal(semaphore* s);
void semaphore_destroy(semaphore* s);

#endif // SEMAPHORE_H