#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "log.h"


void stack_to_string(struct stack_t *stack, char *string)
{
    int length = stack_length(stack);

    for (int i = length-1; i >= 0; i--) {
        string[i] = stack_pop(stack);
    }
    string[length] = '\0';
}

void stack_move(struct stack_t *stack_old, struct stack_t *stack_new)
{
    while (stack_old->top != NULL) {
        stack_push(stack_pop(stack_old), stack_new);
    }
}

void postfix_to_infix(char *postfix, char *infix)
{
    char c;
    struct stack_t *operand_stack = stack_init();
    struct stack_t *infix_stack = stack_init();
    struct stack_t *tmp_infix_stack = stack_init();

    for (int i = 0; i < strlen(postfix); i++) {
        c = postfix[i];
        if (isdigit(c)) {
            stack_push(c, operand_stack);
            continue;
        }

        if (infix_stack->top == NULL) {
            stack_push('(', infix_stack);
            stack_push(stack_pop(operand_stack), infix_stack);
            stack_push(c, infix_stack);
            stack_push(stack_pop(operand_stack), infix_stack);
            stack_push(')', infix_stack);
        } else {
            stack_move(infix_stack, tmp_infix_stack);
            stack_push('(', infix_stack);
            while (tmp_infix_stack->top != NULL) {
                stack_push(stack_pop(tmp_infix_stack), infix_stack);
            }
            stack_push(c, infix_stack);
            stack_push(stack_pop(operand_stack), infix_stack);
            stack_push(')', infix_stack);
        }
    }
    stack_to_string(infix_stack, infix);
    free_stack(infix_stack);
    free_stack(tmp_infix_stack);
    free_stack(operand_stack);
}


int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s EXPRESSION\n", argv[0]);
        exit(1);
    }
    char *infix = malloc(strlen(argv[1]) * 2);
    printf("Expression is %s\n", argv[1]);
    postfix_to_infix(argv[1], infix);
    printf("%s\n", infix);
    free(infix);
}
