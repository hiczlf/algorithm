/*
 * list 头文件
 *
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

node_t *list_get_node(list_t *, int);
node_t *list_get_prev_node(list_t *, int);

void print_list(list_t *);
int list_len(list_t *);

void list_append(list_t *, int);
void list_insert(list_t *, int, int);
int list_get(list_t *, int);

void list_delete(list_t *, int);
