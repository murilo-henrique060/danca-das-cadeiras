// #include "listener.h"
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

    pthread_cond_signal(&listener->cond);

    while (true) {
        ch = getch();

        pthread_mutex_lock(&listener->mutex);
        for (i = 0; i < listener->size; i++) {
            listenerKey = listener->keys[i];
            if (listenerKey == NULL) continue;

            pthread_mutex_lock(&listenerKey->mutex);
            if (!listenerKey->status && listenerKey->key == ch) {
                listenerKey->status = 1;
                pthread_cond_broadcast(&listenerKey->cond);
            }
            pthread_mutex_unlock(&listenerKey->mutex);
        }
        pthread_mutex_unlock(&listener->mutex);
        
        while (listener->size == 0) {
            pthread_cond_wait(&listener->cond, &listener->mutex);
        }

        pthread_testcancel();
    }
}

Listener* listener_init() {
    initscr(); // Initialize ncurses
    cbreak(); // Disable line buffering
    noecho(); // Disable echoing of typed characters
    keypad(stdscr, TRUE); // Enable function keys
    
    Listener* listener = malloc(sizeof(Listener));
    listener->size = 0;
    listener->keys = NULL;
    pthread_mutex_init(&listener->mutex, NULL);
    pthread_cond_init(&listener->cond, NULL);

    pthread_create(&listener->thread, NULL, listener_listen, listener);

    pthread_mutex_lock(&listener->mutex);
    pthread_cond_wait(&listener->cond, &listener->mutex);
    pthread_mutex_unlock(&listener->mutex);

    return listener;
}

void listener_destroy(Listener* listener) {
    pthread_mutex_lock(&listener->mutex);
    
    ListenerKey* listenerKey;
    for (int i = 0; i < listener->size; i++) {
        listenerKey = listener->keys[i];
        if (listenerKey == NULL) continue;

        pthread_mutex_destroy(&listenerKey->mutex);
        pthread_cond_destroy(&listenerKey->cond);
        free(listenerKey);
    }

    pthread_mutex_unlock(&listener->mutex);

    pthread_cancel(listener->thread);

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