#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#define NUM_STEPS_ITERATION 1000000

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
int thread_latest_iteration = 0;
int stop_calculating = 0;
int number_of_threads;

typedef struct iteration_context {
    int start_iteration;
    double *ret_val;
} iteration_context;

void *calculate(void *arg) {
    iteration_context *context = (iteration_context*) arg;
    int thread_current_iteration_count = 0;
    while (1) {
        for (int i = thread_current_iteration_count * NUM_STEPS_ITERATION + context->start_iteration;
             i < (thread_current_iteration_count + 1) * NUM_STEPS_ITERATION;
             i += number_of_threads) {
            *context->ret_val += (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
        }
        pthread_barrier_wait(&barrier);

        pthread_mutex_lock(&mutex_lock);
        if ((stop_calculating == 1) && (thread_current_iteration_count == thread_latest_iteration)) {
            pthread_mutex_unlock(&mutex_lock);
            break;
        } else {
            thread_current_iteration_count++;
            if (thread_latest_iteration < thread_current_iteration_count) {
                thread_latest_iteration = thread_current_iteration_count;
            }
        }
        pthread_mutex_unlock(&mutex_lock);
    }

    pthread_exit(context);
}

void sig_act(int sig) {
    stop_calculating = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "not enough arguments\n");
        exit(EXIT_FAILURE);
    }
    if (((number_of_threads = atoi(argv[1])) == 0) && (number_of_threads < 1)) {
        fprintf(stderr, "wrong number of threads\n");
        exit(EXIT_FAILURE);
    }
    pthread_t *threads;
    if ((threads = (pthread_t *) malloc(number_of_threads * sizeof(pthread_t))) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGINT, sig_act) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    if (pthread_barrier_init(&barrier, NULL, number_of_threads) != 0) {
        perror("barrier");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < number_of_threads; ++ i) {
        iteration_context *context = NULL;
        if ((context = (iteration_context *) malloc(sizeof(iteration_context))) == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        if ((context->ret_val = (double *) malloc(sizeof(double))) == NULL) {
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

    pthread_barrier_destroy(&barrier);
    free(threads);

    pthread_exit(NULL);
}