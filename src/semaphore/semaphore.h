#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} semaphore;

/**
 * @brief Initialize the semaphore.
 * 
 * @param s Pointer to the semaphore.
 * @param initial_count Initial count for the semaphore.
 */
void semaphore_init(semaphore* s, int initial_count);

/**
 * @brief Wait for the semaphore.
 * 
 * This function waits for the semaphore to become available.
 * If another thread is holding the semaphore, it will be blocked until the first one access the semaphore.
 * 
 * @param s Pointer to the semaphore.
 */
void semaphore_wait(semaphore* s);

/**
 * @brief Releases the semaphore that is being held.
 * 
 * This function signals the semaphore, allowing other threads to access it.
 * 
 * @param s Pointer to the semaphore.
 */
void semaphore_signal(semaphore* s);

/**
 * @brief Destroys the semaphore.
 * 
 * This function cleans up the resources used by the semaphore.
 * 
 * @param s Pointer to the semaphore.
 */
void semaphore_destroy(semaphore* s);

#endif // SEMAPHORE_H