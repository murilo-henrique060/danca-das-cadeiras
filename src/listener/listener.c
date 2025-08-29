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
    unsigned int subscribed;
    ListenerKey** keys;
} Listener;

void* listener_listen(void* arg) {
    Listener* listener = (Listener*)arg;
    ListenerKey* listenerKey;
    int ch, i;

    pthread_cond_signal(&listener->cond);

    while (true) {
        printw("listener->keys: ");
        for (int k = 0; k < listener->size; k++) {
            if (listener->keys[k] != NULL) {
            printw("%c ", listener->keys[k]->key);
            } else {
            printw("_ ");
            }
        }
        printw("\n");
        refresh();

        ch = getch();
        printw("Key pressed: %c\n", ch);
        refresh();

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
        
        while (listener->subscribed == 0) {
            pthread_cond_wait(&listener->cond, &listener->mutex);
        }

        pthread_testcancel();
    }
}

Listener* listener_init(unsigned int size) {
    initscr(); // Initialize ncurses
    cbreak(); // Disable line buffering
    noecho(); // Disable echoing of typed characters
    // nodelay(stdscr, TRUE); // Don't block on getch()
    keypad(stdscr, TRUE); // Enable function keys
    
    Listener* listener = malloc(sizeof(Listener));
    listener->size = size;
    listener->subscribed = 0;
    listener->keys = calloc(sizeof(ListenerKey*), size);
    pthread_mutex_init(&listener->mutex, NULL);
    pthread_cond_init(&listener->cond, NULL);

    refresh();

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

unsigned int listener_subscribe(Listener* listener, char key) {
    pthread_mutex_lock(&listener->mutex);

    ListenerKey* listenerKey = malloc(sizeof(ListenerKey));
    pthread_mutex_init(&listenerKey->mutex, NULL);
    pthread_cond_init(&listenerKey->cond, NULL);
    listenerKey->key = key;
    listenerKey->status = 0;

    int i;
    for (i = 0; i < listener->size; i++) {
        if (listener->keys[i] == NULL) {
            listener->keys[i] = listenerKey;
            listener->subscribed++;
            break;
        }
    }
    
    pthread_cond_signal(&listener->cond);
    pthread_mutex_unlock(&listener->mutex);

    return i;
}

void listener_unsubscribe(Listener* listener, unsigned int listenerKeyId) {
    pthread_mutex_lock(&listener->mutex);

    ListenerKey* listenerKey = listener->keys[listenerKeyId];
    pthread_mutex_destroy(&listenerKey->mutex);
    pthread_cond_destroy(&listenerKey->cond);
    free(listenerKey);

    listener->keys[listenerKeyId] = NULL;
    listener->subscribed--;

    pthread_mutex_unlock(&listener->mutex);
}

void listener_wait(Listener* listener, char key) {
    unsigned int listenerKeyId = listener_subscribe(listener, key);
    
    ListenerKey* listenerKey = listener->keys[listenerKeyId];
    pthread_mutex_lock(&listenerKey->mutex);
    while (!listenerKey->status) {
        pthread_cond_wait(&listenerKey->cond, &listenerKey->mutex);
    }
    pthread_mutex_unlock(&listenerKey->mutex);
    
    listener_unsubscribe(listener, listenerKeyId);
}

typedef struct {
    Listener* listener;
    char key;
} WaitForKeyArgs;

void *wait_for_key(void *args)  {
    WaitForKeyArgs* waitArgs = (WaitForKeyArgs*)args;
    Listener* listener = waitArgs->listener;
    char key = waitArgs->key;

    printw("Waiting for key press '%c'...\n", key);
    refresh();
    listener_wait(listener, key);
    printw("Key '%c' pressed!\n", key);
    refresh();
    pthread_exit(NULL);
}

int main() {
    unsigned int size = 5;
    
    Listener* listener = listener_init(size);
    char keys[] = {'a', 'd', 'g', 'j', 'l'};
    pthread_t threads[size];

    printw("Pressione a tecla 'a', 'd', 'g', 'j', ou 'l' para continuar...\n");
    refresh();

    for (int i = 0; i < size; i++) {
        WaitForKeyArgs* args = malloc(sizeof(WaitForKeyArgs));
        args->listener = listener;
        args->key = keys[i];
        pthread_create(&threads[i], NULL, wait_for_key, args);
    }

    for (int i = 0; i < size; i++) {
        pthread_join(threads[i], NULL);
    }

    listener_destroy(listener);
    printf("Programa finalizado!\n");
    return 0;
}