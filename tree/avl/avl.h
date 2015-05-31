#ifndef AVL_H

typedef int avl_element_t;

struct avl_node_t {
    avl_element_t element;
    struct avl_node_t *left;
    struct avl_node_t *right;
    int height;
};

struct avl_node_t *avl_insert(avl_element_t, struct avl_node_t *);

struct avl_node_t *rotate(struct avl_node_t *);

struct avl_node_t *single_rotate_left(struct avl_node_t *);
struct avl_node_t *double_rotate_left(struct avl_node_t *);

struct avl_node_t *single_rotate_right(struct avl_node_t *);
struct avl_node_t *double_rotate_right(struct avl_node_t *);

int height(struct avl_node_t *);

struct avl_node_t *find_max(struct avl_node_t *);
struct avl_node_t *find_min(struct avl_node_t *);

struct avl_node_t *delete(struct avl_node_t *, int);
void avl_free(struct avl_node_t *);

void avl_print(struct avl_node_t *);

#endif
