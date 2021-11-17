#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_QUANTITY_LINES 100
#define SLEEP_COEFFICIENT 10000

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct struct_string {
    char string[1000];
    int size;
} struct_string;

typedef struct Node {
    char *string;
    struct Node *next;
} Node;

Node *head = NULL;

void push_back(char *string) {
    if (head == NULL) {
        if ((head = (Node *) malloc(sizeof(Node))) == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        head->string = string;
        head->next = NULL;
    } else {
        Node *last_node = head;
        while (last_node->next) {
            last_node = last_node->next;
        }
        Node *temp;
        if ((temp = (Node *) malloc(sizeof(Node))) == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        temp->string = string;
        temp->next = NULL;
        last_node->next = temp;
    }
}

void print_list() {
    Node *temp = head;
    while (temp) {
        printf("%s\n", temp->string);
        temp = temp->next;
    }
}

void free_list() {
    Node *prev = NULL;
    while (head->next) {
        prev = head;
        head = head->next;
        free(prev);
    }
    free(head);
}

void *sleep_sort(void *arg) {
    struct_string *strings = (struct_string *) arg;
    usleep(SLEEP_COEFFICIENT * strings->size);

    pthread_mutex_lock(&lock);
    push_back(strings->string);
    pthread_mutex_unlock(&lock);

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

    for (int i = 0; i < n; ++ i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    print_list();
    free_list();
    pthread_mutex_destroy(&lock);

    pthread_exit(NULL);
}