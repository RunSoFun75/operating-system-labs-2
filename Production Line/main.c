#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMBER_OF_FACTORIES 4

sem_t detail_A, detail_B, detail_C, module;

void *create_detail_A(void *arg) {
    int *development_time_of_detail_A = (int *) arg;
    while (1) {
        sleep(*development_time_of_detail_A);
        sem_post(&detail_A);
        printf("detail A created\n");
    }
}

void *create_detail_B(void *arg) {
    int *development_time_of_detail_B = (int *) arg;
    while (1) {
        sleep(*development_time_of_detail_B);
        sem_post(&detail_B);
        printf("detail B created\n");
    }
}

void *create_detail_C(void *arg) {
    int *development_time_of_detail_C = (int *) arg;
    while (1) {
        sleep(*development_time_of_detail_C);
        sem_post(&detail_C);
        printf("detail C created!\n");
    }
}

void *create_module(void *arg) {
    while (1) {
        sem_wait(&detail_A);
        sem_wait(&detail_B);
        sem_post(&module);
        printf("module created!\n");
    }
}

void create_widget() {
    int number_of_widgets = 0;
    while (1) {
        sem_wait(&module);
        sem_wait(&detail_C);
        number_of_widgets++;
        printf("widget created! number of invented widgets: %d\n", number_of_widgets);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    pthread_t threads[NUMBER_OF_FACTORIES];

    sem_init(&detail_A, 0, 0);
    sem_init(&detail_B, 0, 0);
    sem_init(&detail_C, 0, 0);
    sem_init(&module, 0, 0);

    int *development_time_of_detail_A;
    int *development_time_of_detail_B;
    int *development_time_of_detail_C;

    if ((development_time_of_detail_A = (int *) malloc(sizeof(int))) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if ((development_time_of_detail_B = (int *) malloc(sizeof(int))) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if ((development_time_of_detail_C = (int *) malloc(sizeof(int))) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    *development_time_of_detail_A = atoi(argv[1]);
    *development_time_of_detail_B = atoi(argv[2]);
    *development_time_of_detail_C = atoi(argv[3]);

    if (pthread_create(threads, NULL, create_detail_A, (void *) development_time_of_detail_A) != 0) {
        perror("pthread create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(threads + 1, NULL, create_detail_B, (void *) development_time_of_detail_B) != 0) {
        perror("pthread create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(threads + 2, NULL, create_detail_C, (void *) development_time_of_detail_C) != 0) {
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
    free(development_time_of_detail_A);
    free(development_time_of_detail_B);
    free(development_time_of_detail_C);

    pthread_exit(NULL);
}