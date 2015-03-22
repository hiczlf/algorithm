#include "stdio.h"
#include "stack.h"


int main(void) {
    struct stack_t *stack = stack_init();
    push(1, stack);
    push(2, stack);
    push(1001, stack);

    print_stack(stack);
    printf("Pop value is %d\n", pop(stack));
    print_stack(stack);
    printf("stack is empty: %d\n", is_empty(stack));
    pop(stack);
    pop(stack);
    printf("stack is empty: %d\n", is_empty(stack));
}
