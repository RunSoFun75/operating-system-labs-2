#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TWO_SECONDS 2
#define NUMBER_OF_LINES 20

void *print(void *arg) {
    char *text = (char*) arg;
    for (int i = 0; i < NUMBER_OF_LINES; ++ i) {
        printf("%d %s\n", i, text);
        sleep(TWO_SECONDS / 2);
    }

    pthread_exit(arg);
}

int main(int argc, char *argv[]) {
    pthread_t thread;
    char *text = {"line"};

    if (pthread_create(&thread, NULL, print, (void*) text) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    sleep(TWO_SECONDS);

    if (pthread_cancel(thread) != 0) {
        perror("pthread_cancel");
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
}
