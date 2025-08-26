#include "semaphore.h"
#include <pthread.h>

/**
 * @brief Initialize the semaphore.
 * 
 * @param s Pointer to the semaphore.
 * @param initial_count Initial count for the semaphore.
 */
void semaphore_init(semaphore* s, int initial_count) {
    s->count = initial_count;
    pthread_mutex_init(&s->mutex, NULL);
    pthread_cond_init(&s->cond, NULL);
}

/**
 * @brief Wait for the semaphore.
 * 
 * This function waits for the semaphore to become available.
 * If another thread is holding the semaphore, it will be blocked until the first one access the semaphore.
 * 
 * @param s Pointer to the semaphore.
 */
void semaphore_wait(semaphore* s) {
    pthread_mutex_lock(&s->mutex);
    while (s->count <= 0) {
        pthread_cond_wait(&s->cond, &s->mutex);
    }
    s->count--;
    pthread_mutex_unlock(&s->mutex);
}


/**
 * @brief Releases the semaphore that is being held.
 * 
 * This function signals the semaphore, allowing other threads to access it.
 * 
 * @param s Pointer to the semaphore.
 */
void semaphore_signal(semaphore* s) {
    pthread_mutex_lock(&s->mutex);
    s->count++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->mutex);
}

/**
 * @brief Destroys the semaphore.
 * 
 * This function cleans up the resources used by the semaphore.
 * 
 * @param s Pointer to the semaphore.
 */
void semaphore_destroy(semaphore* s) {
    pthread_mutex_destroy(&s->mutex);
    pthread_cond_destroy(&s->cond);
    free(s);
}
