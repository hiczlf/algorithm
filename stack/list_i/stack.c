/* 链表实现的栈 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

struct stack_t *stack_init() {
    struct stack_t *stack = malloc(sizeof(struct stack_t));
    stack->top = NULL;
    return stack;
}

struct stack_node_t *create_stack_node(stack_elem_t value) {
    struct stack_node_t *new_node = malloc(sizeof(struct stack_node_t));
    new_node->value = value;
    return new_node;
}

void push(stack_elem_t value, struct stack_t *stack) {
    struct stack_node_t *new_node = create_stack_node(value);
    new_node->next = stack->top;
    stack->top = new_node;
    return;
}

stack_elem_t pop(struct stack_t *stack) {
    stack_elem_t pop_value;
    struct stack_node_t *pop_node;

    pop_node = stack->top;
    pop_value = pop_node->value;

    stack->top = stack->top->next;
    free(pop_node);
    return pop_value;
}

void print_stack(struct stack_t *stack) {

    struct stack_node_t *node;
    node = stack->top;
    printf("[");
    while(node != NULL) {
       if (node->next == NULL) {
           printf("%d", node->value);
       } else {
           printf("%d, ", node->value);
       }
       node = node->next;
    }
    printf("]\n");
}

bool is_empty(struct stack_t *stack) {
    if (stack == NULL) {
        return 1;
    } else {
        return 0;
    }
}
