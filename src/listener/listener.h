/**
 * @file listener.h
 * @author murilo-henrique060
 * @brief this file contains the implementation of the key listener 
 * @details The implementation of key listener consists of a main listener thread and a function that waits for the key to be stroked.
 *          The lifecycle of the listener must be as follows:
 *              - A listener is created;
 *              - The wait function subscribes a key to be waited, it receives a struct with a flag representing if the key have been stroked;
 *              - The main listener thread listen for every key stroked, and check if any waited key had been stroked, and updates its value;
 *              - The wait function checks until the key have stroked, then unsubscribe the key from the listener;
 *              - The listener is destroyed.
 */

#ifndef LISTENER_H
#define LISTENER_H

/**
 * @brief The listener structure
 */
typedef Listener;

/**
 * @brief Initialize the ncurse library, create a listener and start the listener thread
 * @return A pointer to the created listener
 */
Listener* listener_init();

/**
 * @brief Destroy the listener and free its resources
 */
void listener_destroy(Listener* listener);

#endif // LISTENER_H