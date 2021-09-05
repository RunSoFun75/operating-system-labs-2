#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print(void *arg) {
    for (int i = 0; i < 5; ++ i) {
        printf("CHILD\n");
    }

    pthread_exit(arg);
}

int main(int argc, char *argv[]) {
    pthread_t thread;

    if (pthread_create(&thread, NULL, print, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; ++ i) {
        printf("PARENT\n");
    }

    pthread_exit(NULL);
}