/*
 * cursor 实现
 * 对于cursor, 一直很模糊, 参考数据库概念.
 *
 * 类似数组, 但解决数组的缺点, 如添加删除困难, 空间浪费等等
 * 实现的cursor第一个元素为头
 *
 * 可以说是不使用指针实现链表
 */


typedef unsigned int node_ptr;
typedef int element_type;
typedef int position;

struct _node {
    element_type element;
    node_ptr next;
};

typedef struct _node node_t;

void create_space();
void print_cursor();

position cursor_init(int [], int);
position cursor_find_prev(position, int);
void print_cursor(position);
void cursor_insert(position, int, element_type);
void cursor_del_node(position, int);
void cursor_del(position);

void cursor_free();
position cursor_alloc(void);

