#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_POOL_SIZE 4

volatile int THREAD_INDEX = 0;

typedef struct thread_parameter {
    int size;
    char **strings;
} thread_parameter;

void *print(void *arg) {
    thread_parameter *threads_parameter = (thread_parameter*) arg;
    for (int i = 0; i < (threads_parameter + THREAD_INDEX)->size; ++ i) {
        printf("%s\n", *((threads_parameter + THREAD_INDEX)->strings + i));
    }

    THREAD_INDEX++;
    pthread_exit(arg);
}

int main(int argc, char *argv[]) {
    pthread_t threads[THREAD_POOL_SIZE];

    char *strings[] = {"1", "2", "3", "4", "5", "6", "7", "8"};

    thread_parameter threads_parameter[THREAD_POOL_SIZE];
    for (int i = 0; i < THREAD_POOL_SIZE; ++ i) {
        threads_parameter[i].size = 2;
        threads_parameter[i].strings = strings + 2 * i;
    }

    for (int i = 0; i < THREAD_POOL_SIZE; ++ i) {
        if (pthread_create(&threads[i], NULL, print, (void*) threads_parameter) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
        pthread_join(threads[i], NULL);
    }

    pthread_exit(NULL);
}