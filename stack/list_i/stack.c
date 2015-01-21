#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int value;
    struct _node *next;
} node_t, stack_t;


node_t *create_node(int value) {
    node_t *node = malloc(sizeof(node_t));
    node->value = value;
    return node;
}

stack_t *push(int value, stack_t **stack) {
    node_t *node_new = create_node(value);
    node_new->next = *stack;
    *stack = node_new;
    return *stack;
}

int pop(stack_t **stack) {
    int pop_value;
    node_t *node_first;
    node_first = *stack;
    pop_value = node_first->value;

    *stack = (*stack)->next;
    free(node_first);
    return pop_value;
}

void print_stack(stack_t *stack) {

    node_t *node;
    node = stack;
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

int is_empty(stack_t *stack) {
    if (stack == NULL) {
        return 1;
    } else {
        return 0;
    }
}


int main(void) {
    stack_t *stack = NULL;
    push(100, &stack);
    push(2, &stack);
    push(1001, &stack);

    printf("Pop value is %d\n", pop(&stack));
    print_stack(stack);
    printf("stack is empty: %d\n", is_empty(stack));
    pop(&stack);
    pop(&stack);
    printf("stack is empty: %d\n", is_empty(stack));
}

