#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


int max(int a, int b) {
    return a > b ? a : b;
}

struct avl_node_t * insert(
        avl_element_t value,
        struct avl_node_t *avl_node)
{

    if (avl_node == NULL) {
        avl_node = malloc(sizeof(struct avl_node_t));
        avl_node->element = value;
        avl_node->left = NULL;
        avl_node->right = NULL;
        avl_node->height = 0;
    } else if (value < avl_node->element) {
        avl_node->left = insert(value, avl_node->left);
    } else if (value > avl_node->element) {
        avl_node->right = insert(value, avl_node->right);
    }

    avl_node = rotate(avl_node);
    avl_node->height = max(
            height(avl_node->left),
            height(avl_node->right)) + 1;

    return avl_node;
}

struct avl_node_t *rotate(struct avl_node_t *avl_node)
{
    if ((height(avl_node->left) - height(avl_node->right)) == 2) {
        if (height(avl_node->left->left) > height(avl_node->left->right)) {
            avl_node = single_rotate_right(avl_node);
        } else {
            avl_node = double_rotate_right(avl_node);
        }
    }
    else if ((height(avl_node->left) - height(avl_node->right)) == -2) {
        if (height(avl_node->right->right) > height(avl_node->right->left)) {
            avl_node = single_rotate_left(avl_node);
        } else {
            avl_node = double_rotate_left(avl_node);
        }
    }
    return avl_node;
}

struct avl_node_t *single_rotate_right(struct avl_node_t *avl_node)
{
    struct avl_node_t  *new_root, *old_root;

    old_root = avl_node;
    new_root = avl_node->left;
    old_root->left = new_root->right;
    new_root->right = old_root;

    old_root->height = max(
            height(old_root->left), height(old_root->right)) + 1;

    return new_root;
}

struct avl_node_t *single_rotate_left(struct avl_node_t *avl_node) {
    struct avl_node_t  *new_root, *old_root;

    old_root = avl_node;
    new_root = avl_node->right;
    old_root->right= new_root->left;
    new_root->left= old_root;

    old_root->height = max(
            height(old_root->left), height(old_root->right)) + 1;

    new_root->height = max(
            height(new_root->left), height(new_root->right)) + 1;

    return new_root;
}

struct avl_node_t *double_rotate_right(struct avl_node_t *avl_node) {
    avl_node->left = single_rotate_left(avl_node->left);
    return single_rotate_right(avl_node);
}

struct avl_node_t *double_rotate_left(struct avl_node_t *avl_node) {
    avl_node->left = single_rotate_right(avl_node->left);
    return single_rotate_left(avl_node);
}

int height(struct avl_node_t *avl_node) {

    if  (avl_node == NULL) {
        return -1;
    } else {
        return avl_node->height;
    }
}

/* inorder 打印avl树 */
void _avl_print(struct avl_node_t *avl_node, int indent) {
    if (avl_node == NULL) {
        return;
    }
    _avl_print(avl_node->left, indent + 1);
    printf("%*d\n", indent*4, avl_node->element);
    _avl_print(avl_node->right, indent + 1);
}

/* 包装递归执行的打印树函数(_avl_print)
 * 避免调用时需要提供莫名其妙的缩进数量 */
void avl_print(struct avl_node_t *avl_node) {
    _avl_print(avl_node, 0);
}

struct avl_node_t *find_min(struct avl_node_t *avl_node)
{
    if (avl_node == NULL) {
        return NULL;
    }
    while (avl_node->left != NULL) {
        avl_node = avl_node->left;
    }
    return avl_node;
}

struct avl_node_t *find_max(struct avl_node_t *avl_node)
{
    if (avl_node == NULL) {
        return NULL;
    }
    while (avl_node->right != NULL) {
        avl_node = avl_node->right;
    }
    return avl_node;
}

/* 删除一个节点, 貌似比插入麻烦 */
struct avl_node_t *delete(struct avl_node_t *avl_node, int value) {
    struct avl_node_t *tmp_node;
    if (value < avl_node->element) {
        avl_node->left = delete(avl_node->left, value);
    } else if (value > avl_node->element) {
        avl_node->right = delete(avl_node->right, value);
    } else if (avl_node->left && avl_node->right) {
        tmp_node = find_min(avl_node->right);
        avl_node->element = tmp_node->element;
        avl_node->right = delete(avl_node->right, tmp_node->element);
    } else {
        tmp_node = avl_node;
        if (avl_node->left == NULL) {
            avl_node = avl_node->right;
        } else {
            avl_node = avl_node->left;
        }
        free(tmp_node);
    }
    if (avl_node != NULL) {
        avl_node->height = max(
                height(avl_node->left),
                height(avl_node->right)) + 1;
        avl_node = rotate(avl_node);
    }
    return avl_node;
}

void avl_free(struct avl_node_t *avl_node) {
    if (avl_node->left) {
        avl_free(avl_node->left);
    } else if(avl_node->right) {
        avl_free(avl_node->right);
    }
    free(avl_node);
}

int main(void) {
    struct avl_node_t *min, *max;
    struct avl_node_t *avl_tree= NULL;
    avl_tree = insert(6, avl_tree);
    avl_tree = insert(5, avl_tree);
    avl_tree = insert(4, avl_tree);
    avl_tree = insert(3, avl_tree);
    avl_tree = insert(2, avl_tree);
    avl_tree = insert(1, avl_tree);
    avl_tree = insert(8, avl_tree);
    avl_tree = insert(9, avl_tree);
    avl_tree = insert(10, avl_tree);
    avl_tree = insert(11, avl_tree);
    avl_tree = insert(12, avl_tree);
        avl_tree = insert(1, avl_tree);
    avl_print(avl_tree);
    min = find_min(avl_tree);
    printf("min: %d\n", min->element);
    max = find_max(avl_tree);
    printf("max: %d\n", max->element);
    avl_tree = delete(avl_tree, 12);
    avl_tree = delete(avl_tree, 11);
    /* delete(avl_tree, 10); */
    avl_tree = delete(avl_tree, 9);
    avl_tree = delete(avl_tree, 1);
    avl_tree = delete(avl_tree, 5);
    avl_print(avl_tree);
    avl_free(avl_tree);
}
