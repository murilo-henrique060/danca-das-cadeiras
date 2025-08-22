#include "semaphore/semaphore.h"
#include "listener/listener.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

semaphore *sem;

void* wait_for_key() {
    // Wait for the 'q' key to be pressed
    semaphore_wait(sem);
    listener_wait('q');
    printw("Key 'q' pressed!\n");
    semaphore_signal(sem);
    return NULL;
}

int main() {
    listener_init();
    sem = malloc(sizeof(semaphore));
    semaphore_init(sem, 1);

    pthread_t thread;
    pthread_create(&thread, NULL, wait_for_key, NULL);

    printw("Waiting for 'q' key press...\n"); // Use printw while the listener is active
    refresh(); // Call refresh after printw (apparently it's to apply the changes to the screen but it seems to work without it , but the example I found use it)

    semaphore_wait(sem);

    printw("Exiting listener and semaphore.\n"); // This message should never be seen because the listener is holding the semaphore
    refresh();
    pthread_join(thread, NULL);

    semaphore_signal(sem);

    semaphore_destroy(sem);
    listener_destroy();
    printf("Exiting program.\n");
    return 0;
}
