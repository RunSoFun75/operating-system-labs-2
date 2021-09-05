#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print(void *arguments) {
    for (int i = 0; i < 5; ++ i) {
        printf("CHILD\n");
    }

    pthread_exit(arguments);
}

int main(int argc, char *argv[]) {
    pthread_t thread;

    if (pthread_create(&thread, NULL, print, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; ++ i) {
        printf("PARENT\n");
    }

    pthread_exit(NULL);
}
