#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_STEPS 200000000

int number_of_threads;

typedef struct iteration_context {
    int start_iteration;
    double *ret_val;
} iteration_context;

void *calculate(void *arg) {
    iteration_context *context = (iteration_context*) arg;
    for (int i = context->start_iteration; i < NUM_STEPS; i += number_of_threads) {
        *context->ret_val += (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
    }

    pthread_exit(context);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "not enough arguments\n");
        exit(EXIT_FAILURE);
    }
    if ((number_of_threads = atoi(argv[1])) == 0 && number_of_threads < 1) {
        fprintf(stderr, "wrong number of threads\n");
    }
    pthread_t *threads;
    if ((threads = (pthread_t *) malloc(sizeof(pthread_t) * number_of_threads)) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < number_of_threads; ++ i) {
        iteration_context *context = NULL;
        if ((context = (iteration_context *) malloc(sizeof(iteration_context))) == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        if ((context->ret_val = (double *) malloc(sizeof(double ))) == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        context->start_iteration = i;
        if (pthread_create(&threads[i], NULL, calculate, (void *) context) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    double sum = 0;
    for (int i = 0; i < number_of_threads; ++ i) {
        iteration_context *ret_context;
        if (pthread_join(threads[i], (void **) &ret_context) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
        sum += *ret_context->ret_val;
        free(ret_context->ret_val);
        free(ret_context);
    }
    double pi = 4 * sum;
    printf("pi done - %.15g \n", pi);

    free(threads);

    pthread_exit(NULL);
}