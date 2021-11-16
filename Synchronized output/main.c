#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MUTEX_COUNT 3

pthread_mutex_t mutexes[MUTEX_COUNT];

void destroy_mutexes(int count) {
    for (int i = 0; i < count; ++ i) {
        if (pthread_mutex_destroy(&mutexes[i]) != 0) {
            perror("pthread_mutex_destroy");
            exit(EXIT_FAILURE);
        }
    }
}

void init_mutexes() {
    pthread_mutexattr_t attr;
    if (pthread_mutexattr_init(&attr) != 0) {
        perror("pthread_mutexattr_init");
        exit(EXIT_FAILURE);
    }
    if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK) != 0) {
        perror("pthread_mutexattr_settype");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MUTEX_COUNT; ++ i) {
        if (pthread_mutex_init(&mutexes[i], &attr) != 0) {
            destroy_mutexes(i);
            perror("pthread_mutex_init");
            exit(EXIT_FAILURE);
        }
    }
}

void *second_print(void *arg) {
    pthread_mutex_lock(&mutexes[1]);
    for (int i = 0; i < 5; ++ i) {
        pthread_mutex_lock(&mutexes[0]);
        printf("second: %d\n", i);
        pthread_mutex_unlock(&mutexes[1]);
        pthread_mutex_lock(&mutexes[2]);
        pthread_mutex_unlock(&mutexes[0]);
        pthread_mutex_lock(&mutexes[1]);
        pthread_mutex_unlock(&mutexes[2]);
    }
    pthread_mutex_unlock(&mutexes[1]);
    pthread_exit(arg);
}

void first_print() {
    for (int i = 0; i < 5; ++ i) {
        printf("first: %d\n", i);
        pthread_mutex_lock(&mutexes[2]);
        pthread_mutex_unlock(&mutexes[0]);
        pthread_mutex_lock(&mutexes[1]);
        pthread_mutex_unlock(&mutexes[2]);
        pthread_mutex_lock(&mutexes[0]);
        pthread_mutex_unlock(&mutexes[1]);
    }
    pthread_mutex_unlock(&mutexes[0]);
}


int main(int argc, char *argv[]) {
    pthread_t thread;
    init_mutexes();

    pthread_mutex_lock(&mutexes[0]);

    if (pthread_create(&thread, NULL, second_print, NULL) != 0) {
        perror("pthread_create");
        destroy_mutexes(MUTEX_COUNT);
        exit(EXIT_FAILURE);
    }

    sched_yield();

    first_print();

    destroy_mutexes(MUTEX_COUNT);
    pthread_exit(NULL);
}