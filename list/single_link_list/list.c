#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "log.h"


/* 初始化列表 */
list_t *list_init(int array[], int size)
{
    int index;
    node_t *node, *next_node;
    list_t *list = malloc(sizeof(list_t));
    list->next = NULL;

    for (index=0; index < size; index++) {
        next_node = create_node(array[index]);
        if (index == 0) {
            list->next = next_node;
        } else {
            node->next = next_node;
        }
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

    node_append = create_node(value);

    if (list_len(list) == 0) {
        list->next = node_append;
    } else {
        last_node = list_get_node(list, list_len(list)- 1);
        last_node->next = node_append;
    }

}

/* 打印列表 */
void print_list(list_t *list)
{
    node_t *node_iter = list->next;

    printf("[");
     while(node_iter != NULL) {
        if (node_iter->next == NULL) {
            printf("%d", node_iter->value);
        } else {
            printf("%d, ", node_iter->value);
        }
        node_iter = node_iter->next;
    }
    printf("]\n");
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
    node_t *node_inserted, *prev_node;

    node_inserted = create_node(value);

    /* 插入到索引0处 */
    if (index == 0) {
        node_inserted->next = list->next;
        list->next = node_inserted;
    /* 插入到其他地方 */
    } else {
        prev_node = list_get_prev_node(list, index);
        node_inserted->next = prev_node->next;
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
        prev_node = NULL;
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
    if (index == 0) {
        list->next = node->next;
    } else {
        prev_node = list_get_prev_node(list, index);
        prev_node->next = node->next;
    }
    free(node);
}

/* 删除整个列表 */
void free_list(list_t *list)
{
    node_t *node, *next_node;
    node = list->next;
    free(list);

    while (node != NULL) {
        next_node = node->next;
        free(node);
        node = next_node;
    }
}

/* 使用插入排序对列表进行排序 */
void list_sort(list_t *list)
{
    node_t *sorted_pre, *sorted;
    node_t *unsorted_pre, *unsorted;

    unsorted = list->next;
    while (unsorted != NULL){

        sorted = list->next;
        sorted_pre = NULL;
        while ((unsorted->value >= sorted->value) && \
                (sorted != unsorted)) {
            sorted_pre = sorted;
            sorted = sorted->next;

        }

        /* 当前排序元素满足当前顺序，则进行下一个元素 */
        if (sorted == unsorted) {
            unsorted_pre = unsorted;
            unsorted = unsorted->next;
            continue;
        }

        unsorted_pre->next = unsorted->next;
        unsorted->next = sorted;
        /* 在链表头部插入 */
        if (sorted_pre == NULL){
            list->next = unsorted;
        } else {
            sorted_pre->next = unsorted;
        }
        unsorted = unsorted_pre->next;
    }
}


int main(void) {
    list_t *ids;
    int values[] = {1, 2, -4, 8, 99, 0};
    ids = list_init(values, (sizeof(values) / sizeof(values[0])));
    /* list_append(ids, -7);
    list_append(ids, -6); */
    /* ids = list_sort(ids); */
    print_list(ids);
    printf("The length of list is %d\n", list_len(ids));
    list_sort(ids);
    print_list(ids);
    printf("The length of list is %d\n", list_len(ids));
    /* free_list(ids); */
}
