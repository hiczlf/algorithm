#include "list.h"
#include <stdio.h>
#include <stdlib.h>



void radix_sort(list_t *list)
{
    int base = 10, exp = 1, idx = 0;
    int max;
    int bucket_key;

    list_t *buckets[base];
    node_t *node_next, *node = list->next;
    node_t *bucket_node;

    max = list_abs_max(list);
    while ((max / exp) != 0) {

        /* 初始化buckets数组, 每个bucket对应一个列表 */
        for (idx = 0; idx < base; idx++) {
            buckets[idx] = list_init(NULL, 0);
        }

        /* 将列表中的值放到每个bucket中 */
        node = list->next;
        while (node != NULL) {
            bucket_key = abs(node->value / exp % base);
            list_append(buckets[bucket_key], node->value);
            node = node->next;
        }

        /* 按照buckets索引顺序将bucket中每个列表的值放到原list中,
           完成后的list为按照exp位排好序的值 */
        node = list->next;
        while (node != NULL) {
            for (idx = 0; idx < base; idx++) {
                bucket_node = buckets[idx]->next;
                while (bucket_node != NULL) {
                    node->value = bucket_node->value;
                    node = node->next;
                    bucket_node = bucket_node->next;
                }
            }
        }
        exp *= base;
    }

    /* 将负数放到前面 */
    idx = 0;
    node = list->next;
    while (node != NULL) {
        node_next = node->next;
        if (node->value < 0) {
            list_insert(list, 0, node->value);
            list_del_node(list, idx + 1);
        }
        idx++;
        node = node_next;
    }
}


int main(int argc, char **argv)
{

    int i;
    list_t *ids;
    int values[argc-1];

    printf("Usage: %s int int int ...\n", argv[0]);
    for (i = 1; i < argc; i++) {
        values[i-1] = atoi(argv[i]);
    }

    ids = list_init(values, (sizeof(values) / sizeof(values[0])));
    print_list(ids);
    radix_sort(ids);
    print_list(ids);
    free_list(ids);
    exit(0);
}

