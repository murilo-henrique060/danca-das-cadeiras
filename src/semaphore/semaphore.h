#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <pthread.h>
#include <stdlib.h>

/**
 * @struct semaphore.
 * @brief A counting semaphore for thread synchronization.
 * @details Implements a classic counting semaphore using a mutex and a
 * condition variable to control access to a shared resource by a
 * limited number of threads.
 * * Will limited the number of threads with a count number.
 */
typedef struct {
  int count;             ///< The current value of the semaphore
  pthread_mutex_t mutex; ///< Mutex to ensure atomic operations on the count.
  pthread_cond_t
      cond; ///< Condition variable to block threads when count is zero.
} semaphore;

/**
 * @brief Initialize the semaphore.
 * @param s Pointer to the semaphore.
 * @param initial_count Initial count for the semaphore.
 */
void semaphore_init(semaphore *s, int initial_count);

/**
 * @brief Wait for the semaphore.
 * @details This function waits for the semaphore to become available.
 * If another thread is holding the semaphore, it will be blocked until the
 * first one access the semaphore.
 * @param s Pointer to the semaphore.
 */
void semaphore_wait(semaphore *s);

/**
 * @brief Releases the semaphore that is being held.
 * * This function signals the semaphore, allowing other threads to access it.
 * @param s Pointer to the semaphore.
 */
void semaphore_signal(semaphore *s);

/**
 * @brief Destroys the semaphore.
 * * This function cleans up the resources used by the semaphore.
 * @param s Pointer to the semaphore.
 */
void semaphore_destroy(semaphore *s);

#endif // SEMAPHORE_H
