#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "log.h"


/* 初始化列表 */

list_t *list_init(int array[], int size)
{
    int index;
    list_t *list = malloc(sizeof(list_t));
    node_t *node_iter = list;
    node_t *tmp_node;

    list->value = -1;
    list->next = NULL;

    for (index=0; index < size; index++) {

        tmp_node = malloc(sizeof(list_t));
        tmp_node->value = array[index];
        tmp_node->next = NULL;

        node_iter->next = tmp_node;
        node_iter = tmp_node;
    }
    return list;
}

/* 在列表末尾添加元素 */
void list_append(list_t *list, int value)
{
    node_t *node_append, *node_iter;

    node_iter = list;
    while (node_iter->next != NULL) {
        node_iter = node_iter->next;
    }

    node_append = malloc(sizeof(node_t));
    node_append->value = value;
    node_append->next = NULL;

    node_iter->next = node_append;
}

/* 打印列表 */
void print_list(list_t *list)
{
    node_t *node_iter;

    node_iter = list->next;
    printf("[");
    while (node_iter != NULL) {
        if (node_iter->next == NULL) {
            printf("%d]\n", node_iter->value);
        } else {
            printf("%d, ", node_iter->value);
        }
        node_iter = node_iter->next;
    }
}

/* 得出列表长度 */
int list_len(list_t *list)
{
    int index = 0;
    node_t *node_iter;
    node_iter = list->next;

    while(node_iter != NULL) {
        node_iter = node_iter->next;
        index++;
    }

    return index;
}

void list_insert(list_t *list, int index, int value)
{
    int i;
    node_t *node_inserted;
    node_t *node_iter = list;
    for(i = 1; i < index; i++) {
        node_iter = node_iter->next;
    }

    node_inserted = malloc(sizeof(list_t));
    node_inserted->value = value;
    node_inserted->next = node_iter->next;
    node_iter->next=node_inserted;
}

int list_get(list_t *list, int index)
{
    int i = 1;
    node_t *node_iter = list->next;
    while (i < index && node_iter != NULL) {
        node_iter = node_iter->next;
        i++;
    }
    if (node_iter == NULL) {
        LOG_ERROR("Error: list index out of range!\n");
        exit(1);
    }
    return node_iter->value;
}

int main(void) {
    list_t *ids;
    int values[] = {1, 2, 4, 5, 9};
    ids = list_init(values, 5);
    list_insert(ids, 1, 99);
    list_append(ids, 100);
    print_list(ids);
    printf("The length of list is %d\n", list_len(ids));
    printf("The 2th value of list is %d\n", list_get(ids, 9));
}
