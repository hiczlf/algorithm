#include <stdio.h>
#include <stdlib.h>
#include "list.h"


list_t *list_init()
{
    list_t *list = malloc(sizeof(list_t));
    list->next = NULL;
    return list;
}

void list_append(list_t *list, int value)
{
    node_t *node_append, *node_iter;

    node_iter = list->next;
    while (node_iter != NULL) {
        node_iter = node_iter->next;
    }

    node_append = malloc(sizeof(node_t));
    node_append->value = value;
    node_append->next = NULL;

    node_iter->next = node_append;
}

void print_list(list_t *list) {
    node_t *node_iter;

    printf("[");
    node_iter = list->next;
    while (node_iter != NULL) {
        printf("%d, ", node_iter->value);
        node_iter = node_iter->next;
    }
    printf("]\n");
}

int main(void) {
    list_t *ids;
    ids = list_init();
    list_append(ids, 1);
    print_list(ids);
}
