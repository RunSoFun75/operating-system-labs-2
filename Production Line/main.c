#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMBER_OF_FACTORIES 4

sem_t detail_A, detail_B, detail_C, module;

void *create_detail_A(void *arg) {
    while (1) {
        sleep(1);
        sem_post(&detail_A);
        printf("detail A created\n");
    }
}

void *create_detail_B(void *arg) {
    while (1) {
        sleep(2);
        sem_post(&detail_B);
        printf("detail B created\n");
    }
}

void *create_detail_C(void *arg) {
    while(1) {
        sleep(3);
        sem_post(&detail_C);
        printf("detail C created!\n");
    }
}

void *create_module(void *arg) {
    while(1){
        sem_wait(&detail_A);
        sem_wait(&detail_B);
        sem_post(&module);
        printf("module created!\n");
    }
}

void create_widget() {
    while(1) {
        sem_wait(&module);
        sem_wait(&detail_C);
        printf("widget created!\n");
    }
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUMBER_OF_FACTORIES];

    sem_init(&detail_A, 0, 0);
    sem_init(&detail_B, 0, 0);
    sem_init(&detail_C, 0, 0);
    sem_init(&module, 0, 0);

    if (pthread_create(threads, NULL, create_detail_A, NULL) != 0) {
        perror("pthread create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(threads + 1, NULL, create_detail_B, NULL) != 0) {
        perror("pthread create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(threads + 2, NULL, create_detail_C, NULL) != 0) {
        perror("pthread create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(threads + 3, NULL, create_module, NULL) != 0) {
        perror("pthread create");
        exit(EXIT_FAILURE);
    }

    create_widget();

    sem_destroy(&detail_A);
    sem_destroy(&detail_B);
    sem_destroy(&detail_C);
    sem_destroy(&module);

    pthread_exit(NULL);
}