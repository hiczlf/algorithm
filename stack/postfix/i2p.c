#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "log.h"

int get_privilege(char operator) {

    unsigned int privilege;
    switch(operator) {
    case '+':
    case '-':
        privilege = 5;
        break;
    case '*':
    case '/':
        privilege = 10;
        break;
    case '(':
    case ')':
        privilege = 20;
    case '\0':
        privilege = 0;
        break;
    default:
        fprintf(stderr, "unrecognize operator");
        exit(1);
    }
    return privilege;
}

void push_operator(char c,
        struct stack_t *postfix_stack,
        struct stack_t *operator_stack)
{
    char operator;
    int privilege_c = get_privilege(c);

    /* 如果遇到括号 */
    if (c == '(') {
        stack_push(c, operator_stack);
    } else if (c == ')') {
        do {
            operator = stack_pop(operator_stack);
            stack_push(operator, postfix_stack);
        } while (operator != '(');
        stack_pop(postfix_stack);

    } else if (stack_is_empty(operator_stack)) {
        stack_push(c, operator_stack);
    } else if (privilege_c >= get_privilege(stack_head(operator_stack))) {
        stack_push(c, operator_stack);
    } else {
        do {
            operator = stack_pop(operator_stack);
            stack_push(operator, postfix_stack);
        } while(!stack_is_empty(operator_stack) &&
                privilege_c <= get_privilege(stack_head(operator_stack)));
        stack_push(c, operator_stack);
    }
}

void stack_to_string(struct stack_t *stack, char *string)
{
    int length = stack_length(stack);

    for (int i = length-1; i >= 0; i--) {
        string[i] = stack_pop(stack);
    }
    string[length] = '\0';
}

void infix_to_postfix(char *infix, char *postfix)
{
    char c;
    struct stack_t *operator_stack = stack_init();
    struct stack_t *postfix_stack = stack_init();

    for (int i = 0; i < strlen(infix); i++) {
        c = infix[i];
        if (isdigit(c)) {
            stack_push(c, postfix_stack);
        } else {
            push_operator(c, postfix_stack, operator_stack);
        }
    }
    push_operator('\0', postfix_stack, operator_stack);
    stack_to_string(postfix_stack, postfix);
    free_stack(postfix_stack);
    free_stack(operator_stack);
}


int main(int argc, char *argv[]) {

    char *postfix = malloc(strlen(argv[1]));
    if (argc != 2) {
        printf("Usage: %s EXPRESSION\n", argv[0]);
        exit(1);
    }
    printf("Expression is %s\n", argv[1]);
    infix_to_postfix(argv[1], postfix);
    printf("%s\n", postfix);
    free(postfix);
}
