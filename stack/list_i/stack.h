#include <stdbool.h>

#ifndef _STACK_H

#define _STACK_H

typedef int stack_elem_t;

struct stack_node_t {
    stack_elem_t value;
    struct stack_node_t *next;
};

struct stack_t {
    struct stack_node_t *top;
};


struct stack_t *stack_init();
struct stack_node_t *create_stack_node(stack_elem_t value);
void push(stack_elem_t value, struct stack_t *stack);
stack_elem_t pop(struct stack_t *stack);
void print_stack(struct stack_t *stack);
bool is_empty(struct stack_t *stack);

#endif
