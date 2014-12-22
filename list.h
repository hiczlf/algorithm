/*
 * list 头文件
 *
 * list 从1开始, 链表第一个为头
 * 其他尽量模仿python list
 */


struct _node {
    int  value;
    struct _node *next;
};


typedef struct _node node_t;
typedef node_t list_t;


/* list函数声明 */
list_t *list_init(int arr[], int size);
int list_len(list_t *);
void list_append(list_t *, int);
void print_list(list_t *);
int list_get(list_t *, int);

