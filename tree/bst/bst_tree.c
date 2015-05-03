#include <stdio.h>
#include <stdlib.h>
#include "bst_tree.h"

bst_tree_t *bst_insert(
        bst_elem_t value, bst_tree_t *tree)
{
    if (tree == NULL) {
        tree = malloc(sizeof(bst_tree_t));
        if (tree == NULL) {
            fprintf(stderr, "Out of space");
            exit(1);
        } else {
            tree->elem = value;
            tree->left = tree->right = NULL;
        }
    }
    else if (value < tree->elem) {
        tree->left = bst_insert(value, tree->left);
    }
    else if (value > tree->elem){
        tree->right = bst_insert(value, tree->right);
    }
    return tree;
}

void bst_print(bst_tree_t *tree)
{
    if (tree == NULL) {
        return;
    }

    bst_print(tree->left);
    printf("%d ", tree->elem);
    bst_print(tree->right);
}

bst_tree_t *bst_make_empty(bst_tree_t *tree)
{
    if (tree != NULL) {
        bst_make_empty(tree->left);
        bst_make_empty(tree->right);
        free(tree);
    }
    return NULL;
}

bst_tree_t *bst_find(bst_elem_t value, bst_tree_t *tree)
{
    if (tree == NULL) {
        return NULL;
    }

    if (value < tree->elem) {
        tree = bst_find(value, tree->left);
    } else if (value > tree->elem) {
        tree = bst_find(value, tree->right);
    }
    return tree;
}

bst_tree_t *bst_find_min(bst_tree_t *tree)
{
    if (tree == NULL) {
        return NULL;
    }
    if (tree->left == NULL) {
        return tree;
    } else {
        return bst_find_min(tree->left);
    }
}

bst_tree_t *bst_find_max(bst_tree_t *tree)
{
    if (tree == NULL) {
        return NULL;
    }

    if (tree->right == NULL) {
        return tree;
    } else {
        return bst_find_max(tree->right);
    }
}

bst_tree_t *bst_delete(bst_elem_t value, bst_tree_t *tree)
{
    struct bst_node_t *tmp_node;
    if (tree == NULL) {
        return NULL;
    } else if (value < tree->elem) {
        tree->left = bst_delete(value, tree->left);
    } else if (value > tree->elem) {
        tree->right = bst_delete(value, tree->right);
    } else if (tree->left && tree->right) {
        tmp_node = bst_find_min(tree->right);
        tree->elem = tmp_node->elem;
        tree->right = bst_delete(tree->elem, tree->right);
    } else {
        tmp_node = tree;
        if (tree->left == NULL) {
            tree = tree->right;
        } else if (tree->right == NULL) {
            tree = tree->left;
        }
        free(tmp_node);
    }
    return tree;
}


int main(void) {
    bst_tree_t *tree = NULL;
    tree = bst_insert(1, tree);
    tree = bst_insert(8, tree);
    tree = bst_insert(2, tree);
    tree = bst_insert(4, tree);
    tree = bst_insert(10, tree);
    tree = bst_insert(7, tree);
    bst_print(tree);
    printf("\n");
    tree = bst_delete(8, tree);
    bst_print(tree);
    printf("\n");
    bst_make_empty(tree);
}
