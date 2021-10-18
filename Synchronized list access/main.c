#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define STRING_SIZE 80

const char *TO_PRINT = "";
pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct Node {
    char string[STRING_SIZE];
    struct Node *next;
} Node;

Node *head = NULL;

void push(const char *string) {
    pthread_mutex_lock(&mutex_lock);
    Node *temp;
    if ((temp =  (Node *) malloc(sizeof(Node))) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(temp->string, string);
    temp->next = head;
    head = temp;
    pthread_mutex_unlock(&mutex_lock);
}

void print_list() {
    pthread_mutex_lock(&mutex_lock);
    Node *temp = head;
    while (temp) {
        printf("%s\n", temp->string);
        temp = temp->next;
    }
    pthread_mutex_unlock(&mutex_lock);
}

void free_list() {
    pthread_mutex_lock(&mutex_lock);
    Node *prev = NULL;
    while (head->next) {
        prev = head;
        head = head->next;
        free(prev);
    }
    free(head);
    pthread_mutex_unlock(&mutex_lock);
}

void *sort(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex_lock);
        if (head != NULL) {
            for (Node *iter1 = head; iter1->next != NULL; iter1 = iter1->next) {
                for (Node *iter2 = iter1->next; iter2 != NULL; iter2 = iter2->next) {
                    if (strcmp(iter1->string, iter2->string) > 0) {
                        char temp[STRING_SIZE];
                        strcpy(temp, iter1->string);
                        strcpy(iter1->string, iter2->string);
                        strcpy(iter2->string, temp);
                    }
                }
            }
        }
        pthread_mutex_unlock(&mutex_lock);
        sleep(5);
    }
}

int main(int argc, char *argv[]) {
    pthread_t thread;
    if (pthread_create(&thread, NULL, sort, NULL) != 0) {
        perror("pthread create");
        exit(EXIT_FAILURE);
    }

    char buf[STRING_SIZE];
    while (1) {
        if (fgets(buf, STRING_SIZE, stdin) == NULL) {
            pthread_cancel(thread);
            pthread_join(thread, NULL);
            free_list();
            pthread_mutex_destroy(&mutex_lock);
            pthread_exit(NULL);
        }

        int length = (int) strlen(buf);
        if (buf[length - 1] == '\n') {
            buf[length - 1] = '\0';
        }

        if (!strcmp(buf, TO_PRINT)) {
            print_list();
        } else {
            push(buf);
        }
    }
}
