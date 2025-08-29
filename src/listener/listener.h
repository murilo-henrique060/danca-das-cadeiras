/**
 * @file listener.h
 * @author murilo-henrique060
 * @brief this file contains the implementation of the key listener 
 * @details The implementation of key listener consists of a main listener thread and a function that waits for the key to be stroked.
 *          The ncurses must be initialized before it initialiization
 *          The lifecycle of the listener must be as follows:
 *              - A listener is created;
 *              - The wait function subscribes a key to be waited, it receives a struct with a flag representing if the key have been stroked;
 *              - The main listener thread listen for every key stroked, and check if any waited key had been stroked, and updates its value;
 *              - The wait function checks until the key have stroked, then unsubscribe the key from the listener;
 *              - The listener is destroyed.
 */

#ifndef LISTENER_H
#define LISTENER_H

#include <pthread.h>

/**
 * @brief The waited key structure
 * @details The waited key structure contains the key to be listened to and its status.
 */
typedef struct {
    char key; ///< The key to be listened to
    unsigned int status; ///< The status of the key (0 = not pressed, 1 = pressed)
    pthread_mutex_t mutex; ///< Mutex to protect access to the key status
    pthread_cond_t cond; ///< Condition variable to wait for the key press
} ListenerKey;

/**
 * @brief The listener structure
 * @details The listener structure contains the main listener thread and a list of keys to be listened to.
 *          It also contains synchronization primitives to protect access to the key list.
 *          The key list is dynamically allocated and can grow as needed.
 */
typedef struct {
    pthread_t thread; ///< The main listener thread

    pthread_mutex_t mutex; ///< Mutex to protect access to the listener
    pthread_cond_t cond; ///< Condition variable to wait for key events

    unsigned int size; ///< The number of keys being listened to
    ListenerKey** keys; ///< The list of keys being listened to
} Listener;

/**
 * @brief The main listener thread function
 * @details This function listens for key events and notifies the corresponding listener keys.
 * @param arg Pointer to the listener structure
 */
void* listener_listen(void* arg);

/**
 * @brief Initialize the ncurse library, create a listener and start the listener thread
 * @return A pointer to the created listener
 */
Listener* listener_init();

/**
 * @brief Destroy the listener and free its resources
 */
void listener_destroy(Listener* listener);

/**
 * @brief Subscribe a key to the listener
 * @details This function creates a new listener key and adds it to the listener's key list.
 * @param listener Pointer to the listener structure
 * @param key The key to be subscribed
 * @return A pointer to the created listener key
 */
ListenerKey* listener_subscribe(Listener* listener, char key);

/**
 * @brief Unsubscribe a key from the listener
 * @details This function removes a listener key from the listener's key list and frees its resources.
 * @param listener Pointer to the listener structure
 * @param listenerKey Pointer to the listener key to be unsubscribed
 */
void listener_unsubscribe(Listener* listener, ListenerKey* listenerKey);

/**
 * @brief Wait for a key to be pressed
 * @details This function subscribes a key to the listener and waits for it to be pressed.
 * @param listener Pointer to the listener structure
 * @param key The key to be waited for
 */
void listener_wait(Listener* listener, char key);

#endif // LISTENER_H