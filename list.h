/*
 * list 头文件
 */


struct _node {
    int  value;
    struct _node *next;
};

struct _head {
    struct _node *next;
};

typedef struct _node node_t;
typedef struct _head list_t;


/* list函数生命 */
int list_len(list_t);
void list_append(list_t *, int);
void print_list(list_t *);

