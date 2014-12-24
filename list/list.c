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
    node_t *last_node, *node_append;
    int list_length = list_len(list);

    last_node = list_get_node(list, list_length - 1);

    node_append = malloc(sizeof(node_t));
    node_append->value = value;
    node_append->next = NULL;

    last_node->next = node_append;
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

/* 在指定索引处插入数据 */
void list_insert(list_t *list, int index, int value)
{
    node_t *prev_node, *node_inserted;

    prev_node = list_get_prev_node(list, index);
    node_inserted = malloc(sizeof(list_t));
    node_inserted->value = value;
    node_inserted->next = prev_node->next;
    prev_node->next=node_inserted;
}


/* 获取列表中指定索引对应的值*/
int list_get(list_t *list, int index)
{
    node_t * node;
    node = list_get_node(list, index);
    return node->value;
}

/* 获取列表中指定索引对应的node */
node_t *list_get_node(list_t *list, int index)
{
    int i = 0;
    node_t *node = list->next;
    while (i < index && node != NULL) {
        node = node ->next;
        i++;
    }
    if (node == NULL) {
        LOG_ERROR("Error: list index out of range!\n");
        exit(1);
    }
    return node;
}

/* 获取列表中指定索引上一个node */
node_t *list_get_prev_node(list_t *list, int index)
{
    node_t *prev_node;
    if (index == 0) {
        prev_node = list;
    } else {
        prev_node = list_get_node(list, index-1);
    }
    return prev_node;
}

/* 删除列表中索引对应的node */
void list_del_node(list_t *list, int index)
{
    node_t *node, *prev_node;
    node = list_get_node(list, index);
    prev_node = list_get_prev_node(list, index);
    prev_node->next = node->next;
    free(node);
}

/* 删除整个列表 */
void free_list(list_t *list)
{
    node_t *node, *next_node;
    node = list;

    while (node != NULL) {
        next_node = node->next;
        free(node);
        node = next_node;
    }
}


int main(void) {
    list_t *ids;
    int values[] = {1, 2, 4, 5, 9};
    ids = list_init(values, 5);
    print_list(ids);
    printf("The length of list is %d\n", list_len(ids));
    list_del_node(ids, 1);
    print_list(ids);
    printf("The length of list is %d\n", list_len(ids));
    free_list(ids);
}
