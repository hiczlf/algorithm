#include <stdio.h>
#include <stdlib.h>
#include "cursor.h"
#include "log.h"

#define SPACE_LENGTH 500
node_t CURSOR_SPACE[SPACE_LENGTH];


void print_cursor(position head)
{
    position p = CURSOR_SPACE[head].next;

    printf("[");
    while (p != 0) {
        if (CURSOR_SPACE[p].next == 0) {
            printf("%d", CURSOR_SPACE[p].element);
        } else {
            printf("%d, ", CURSOR_SPACE[p].element);
        }
        p = CURSOR_SPACE[p].next;
    }
    printf("]\n");
}

position cursor_init(int array[], int size)
{
    position head, current, next;

    head = cursor_alloc();
    current = head;
    CURSOR_SPACE[head].next = 0;

    for (int i = 0; i < size; i++) {
        next = cursor_alloc();
        CURSOR_SPACE[current].next = next;

        CURSOR_SPACE[next].element = array[i];
        current = next;
    }
    CURSOR_SPACE[current].next = 0;
    return head;
}

void create_space()
{
    int space_length = sizeof(CURSOR_SPACE) / sizeof(CURSOR_SPACE[0]);

    for (int i = 0; i < space_length; i++) {
        CURSOR_SPACE[i].next = i + 1;
    }
}

position cursor_find_prev(position cursor, int idx)
{
    position p = cursor;
    int idx_pre = -1;
    while (p != 0 && idx_pre != idx -1) {
        idx_pre++;
        p = CURSOR_SPACE[p].next;
    }

    if (p == 0) {
        LOG_ERROR("ERROR: index out of range\n");
        exit(1);
    }
    return p;
}

void cursor_insert(position cursor, int idx, element_type value)
{
    position p_prev, insert_p;

    p_prev = cursor_find_prev(cursor, idx);
    insert_p = cursor_alloc();
    CURSOR_SPACE[insert_p].element = value;
    CURSOR_SPACE[insert_p].next = CURSOR_SPACE[p_prev].next;
    CURSOR_SPACE[p_prev].next = insert_p;

}

void cursor_del_node(position cursor, int idx)
{
    position p_prev, p;
    p_prev = cursor_find_prev(cursor, idx);
    p = CURSOR_SPACE[p_prev].next;
    CURSOR_SPACE[p_prev].next = CURSOR_SPACE[p].next;
    cursor_free(p);
}

void cursor_del(position cursor)
{
    position p, p_next;
    p = cursor;
    while (p != 0) {
        /* 实时上此处不需要额外变量保存p,
         * 因为p free后, 其实里面存储的东西并没有清空.
         * 但是我认为不应该依赖实现细节, 所以使用了额外变量 */
        p_next = CURSOR_SPACE[p].next;
        cursor_free(p);
        p = p_next;
    }
}

position cursor_alloc()
{
    position p;

    p = CURSOR_SPACE[0].next;
    CURSOR_SPACE[0].next = CURSOR_SPACE[p].next;
    return p;
}

void cursor_free(position p)
{
    CURSOR_SPACE[p].next = CURSOR_SPACE[0].next;
    CURSOR_SPACE[0].next = p;
}


int main(int argc, char **argv)
{
    position cursor;
    element_type values[argc-1];
    printf("Usage: %s int int int ...\n", argv[0]);

    for (int i = 1; i < argc; i++) {
        values[i-1] = atoi(argv[i]);
    }

    create_space();
    cursor = cursor_init(values, sizeof(values)/sizeof(values[0]));
    print_cursor(cursor);
    cursor_del(cursor);
}
