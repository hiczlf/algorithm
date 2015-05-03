#ifndef _bst_h

typedef int bst_elem_t;
struct bst_node_t {
    bst_elem_t elem;
    struct bst_node_t * left;
    struct bst_node_t * right;
};

typedef struct bst_node_t bst_tree_t;


bst_tree_t *bst_insert(bst_elem_t value, bst_tree_t *tree);
void bst_print(bst_tree_t *tree);
bst_tree_t * bst_make_empty(bst_tree_t *tree);
bst_tree_t * bst_find(bst_elem_t value, bst_tree_t *tree);
bst_tree_t * bst_find_min(bst_tree_t *tree);
bst_tree_t * bst_find_m(bst_tree_t *tree);

#endif

