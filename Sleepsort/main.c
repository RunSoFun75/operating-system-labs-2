#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define MAX_QUANTITY_LINES 100
#define SLEEP_COEFFICIENT 10000

typedef struct struct_string {
    char string[1000];
    int size;
} struct_string;

void *sleep_sort(void *arg) {
    struct_string *strings = (struct_string *) arg;
    usleep(SLEEP_COEFFICIENT * strings->size);
    printf("%s\n", strings->string);

    pthread_exit(arg);
}

int main(int argc, char *argv[]) {
    pthread_t threads[MAX_QUANTITY_LINES];
    struct_string strings[MAX_QUANTITY_LINES];

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", strings[i].string);
        strings[i].size = strlen(strings[i].string);
    }

    for (int i = 0; i < n; ++ i) {
        if (pthread_create(&threads[i], NULL, sleep_sort, (void *) (strings + i)) != 0) {
            perror("pthread create");
            exit(EXIT_FAILURE);
        }
    }

    pthread_exit(NULL);
}