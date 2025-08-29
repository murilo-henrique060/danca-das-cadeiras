#include "listener.h"
#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    char key;
    unsigned int status;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} ListenerKey;

typedef struct {
    pthread_t thread;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
    
    unsigned int size;
    ListenerKey** keys;
} Listener;

void* listener_listen(void* arg) {
    Listener* listener = (Listener*)arg;
    ListenerKey* listenerKey;
    int ch, i;

    pthread_cond_signal(&listener->cond); // Notify waiting threads

    // Main listening loop
    while (true) {
        ch = getch(); // Get the pressed key, if many keys are pressed at once, each call to getch will get the next one in order

        pthread_mutex_lock(&listener->mutex); // Lock the listener to search for the key
        for (i = 0; i < listener->size; i++) { // Iterate over the listener keys
            listenerKey = listener->keys[i];
            if (listenerKey == NULL) continue;

            pthread_mutex_lock(&listenerKey->mutex);  // Lock the listener key to update its status
            if (!listenerKey->status && listenerKey->key == ch) { // Check if the key is the one being listened to
                listenerKey->status = 1; // Mark the key as pressed
                pthread_cond_broadcast(&listenerKey->cond); // Notify waiting threads
            }
            pthread_mutex_unlock(&listenerKey->mutex); // Unlock the listener key
        }
        pthread_mutex_unlock(&listener->mutex); // Release the listener lock

        while (listener->size == 0) { // Wait for keys to be added
            pthread_cond_wait(&listener->cond, &listener->mutex);
        }

        pthread_testcancel(); // Check for cancellation requests, in case of a listener_destroy call 
    }
}

Listener* listener_init() {
    initscr(); // Initialize ncurses
    cbreak(); // Disable line buffering
    noecho(); // Disable echoing of typed characters
    keypad(stdscr, TRUE); // Enable function keys

    Listener* listener = malloc(sizeof(Listener)); // Allocate memory for the listener, and initialize it
    listener->size = 0;
    listener->keys = NULL;
    pthread_mutex_init(&listener->mutex, NULL);
    pthread_cond_init(&listener->cond, NULL);

    pthread_create(&listener->thread, NULL, listener_listen, listener); // Create the listener thread

    pthread_mutex_lock(&listener->mutex); // Wait for the listener thread to initialize
    pthread_cond_wait(&listener->cond, &listener->mutex);
    pthread_mutex_unlock(&listener->mutex);

    return listener; // Return the initialized listener
}

void listener_destroy(Listener* listener) {
    pthread_mutex_lock(&listener->mutex); // Lock the listener mutex to free its listenerKeys resources

    ListenerKey* listenerKey;
    for (int i = 0; i < listener->size; i++) { // Iterate over the listener keys and free their resources
        listenerKey = listener->keys[i];
        if (listenerKey == NULL) continue;

        pthread_mutex_destroy(&listenerKey->mutex);
        pthread_cond_destroy(&listenerKey->cond);
        free(listenerKey);
    }

    pthread_mutex_unlock(&listener->mutex); // Unlock the listener mutex


    pthread_cancel(listener->thread); // Cancel the listener thread

    
    pthread_mutex_destroy(&listener->mutex); 
    pthread_cond_destroy(&listener->cond);
    free(listener->keys);
    free(listener);
}

ListenerKey* listener_subscribe(Listener* listener, char key) {
    pthread_mutex_lock(&listener->mutex);

    ListenerKey* listenerKey = malloc(sizeof(ListenerKey));
    pthread_mutex_init(&listenerKey->mutex, NULL);
    pthread_cond_init(&listenerKey->cond, NULL);
    listenerKey->key = key;
    listenerKey->status = 0;

    listener->keys = realloc(listener->keys, sizeof(ListenerKey*) * (listener->size + 1));
    listener->keys[listener->size] = listenerKey;
    listener->size++;

    pthread_cond_signal(&listener->cond);
    pthread_mutex_unlock(&listener->mutex);

    return listenerKey;
}

void listener_unsubscribe(Listener* listener, ListenerKey* listenerKey) {
    pthread_mutex_lock(&listener->mutex);

    unsigned int listenerKeyId = 0;
    for (int i = 0; i < listener->size; i++) {
        listenerKeyId = i;
        if (listener->keys[i] == listenerKey) {
            break;
        }
    }
    
    pthread_mutex_destroy(&listenerKey->mutex);
    pthread_cond_destroy(&listenerKey->cond);
    free(listenerKey);

    listener->size--;
    listener->keys[listenerKeyId] = listener->keys[listener->size];
    listener->keys = realloc(listener->keys, sizeof(ListenerKey*) * listener->size);

    pthread_mutex_unlock(&listener->mutex);
}

void listener_wait(Listener* listener, char key) {
    ListenerKey* listenerKey = listener_subscribe(listener, key);
    
    pthread_mutex_lock(&listenerKey->mutex);
    while (!listenerKey->status) {
        pthread_cond_wait(&listenerKey->cond, &listenerKey->mutex);
    }
    pthread_mutex_unlock(&listenerKey->mutex);
    
    listener_unsubscribe(listener, listenerKey);
}

typedef struct {
    Listener* listener;
    char key;
} WaitForKeyArgs;