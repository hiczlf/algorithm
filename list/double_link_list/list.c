#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "log.h"


/* 初始化列表 */
list_t *list_init(int array[], int size)
{
    int index;
    list_t *list;
    node_t *node, *next_node;

    if (size == 0) {
        return NULL;
    }

    node = create_node(array[0]);
    list = node;

    for (index=1; index < size; index++) {
        next_node = create_node(array[index]);

        next_node->previous = node;
        node->next = next_node;

        node = next_node;
    }

    return list;
}

/* 创建一个列表节点 */
node_t *create_node(int value)
{
    node_t *node;
    node = malloc(sizeof(node_t));
    node->value = value;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

/* 交换两个节点内容 */
void swap_node(node_t *prev_node, node_t *next_node)
{
    node_t tmp_node = *prev_node;
    *prev_node = *next_node;
    *next_node = tmp_node;
}

/* 在列表末尾添加元素 */
void list_append(list_t *list, int value)
{
    node_t *last_node, *node_append;

    last_node = list_get_node(list, list_len(list)- 1);
    node_append = create_node(value);

    node_append->previous = last_node;
    last_node->next = node_append;
}

/* 打印列表 */
void print_list(list_t *list)
{
    node_t *node_iter = list;
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
    node_iter = list;

    while(node_iter != NULL) {
        node_iter = node_iter->next;
        index++;
    }

    return index;
}

/* 在指定索引处插入数据 */
void list_insert(list_t *list, int index, int value)
{
    node_t *prev_node, *next_node, *node_inserted;

    next_node = list_get_node(list, index);
    prev_node = next_node->previous;

    node_inserted = create_node(value);

    /* 如果在列表头部插入 */
    if (prev_node == NULL) {
        node_inserted->previous = NULL;
        node_inserted->next = node_inserted;
        next_node->previous = next_node;

        swap_node(next_node, node_inserted);

    /* 在其他地方插入 */
    } else {
        node_inserted->previous = prev_node;
        node_inserted->next = next_node;

        next_node->previous = node_inserted;
        prev_node->next=node_inserted;
    }

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
    node_t *node = list;
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


/* 删除列表中索引对应的node */
void list_del_node(list_t *list, int index)
{
    node_t *node;
    node = list_get_node(list, index);
    /* 删除第一个节点 */
    if (node->previous == NULL) {
        swap_node(node, node->next);
        free(node->next);
        node->previous = NULL;
    /* 删除其他节点 */
    } else {
        node->previous->next = node->next;
        free(node);
    }
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
    list_insert(ids, 0, 0);
    list_append(ids, 100);
    print_list(ids);
    printf("The length of list is %d\n", list_len(ids));
    list_del_node(ids, 0);
    print_list(ids);
    free_list(ids);
}
