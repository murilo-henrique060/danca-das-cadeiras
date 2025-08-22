#include "semaphore.h"
#include <pthread.h>

void semaphore_init(semaphore* s, int initial_count) {
    s->count = initial_count;
    pthread_mutex_init(&s->mutex, NULL);
    pthread_cond_init(&s->cond, NULL);
}

void semaphore_wait(semaphore* s) {
    pthread_mutex_lock(&s->mutex);
    while (s->count <= 0) {
        pthread_cond_wait(&s->cond, &s->mutex);
    }
    s->count--;
    pthread_mutex_unlock(&s->mutex);
}

void semaphore_signal(semaphore* s) {
    pthread_mutex_lock(&s->mutex);
    s->count++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->mutex);
}

void semaphore_destroy(semaphore* s) {
    pthread_mutex_destroy(&s->mutex);
    pthread_cond_destroy(&s->cond);
    free(s);
}
