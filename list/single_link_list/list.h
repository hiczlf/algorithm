/*
 * list 头文件
 * 实现单链表
 * 里面存的值为整形(signed int)
 *
 * 其他尽量模仿python list
 */

#ifndef _LIST_H
#define _LIST_H

struct _node {
    int  value;
    struct _node *next;
};

struct _head {
    struct _node *next;
    struct _node *tail;
};


typedef struct _node node_t;
typedef struct _head list_t;


/* list函数声明 */
list_t *list_init(int arr[], int size);
node_t *create_node(int value);

node_t *list_get_node(list_t *, int);
node_t *list_get_prev_node(list_t *, int);


void print_list(list_t *);
int list_len(list_t *);
int list_abs_max(list_t *);

void list_append(list_t *, int);
void list_insert(list_t *, int, int);
int list_get(list_t *, int);
void list_sort(list_t *list);

void swap_node(node_t*, node_t*);
void list_del_node(list_t *, int);
void free_list(list_t *);

#endif
