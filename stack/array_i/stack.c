/* 数组实现栈 */
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

#define SIZE 500

typedef struct _stack_t {
    int array[SIZE];
    int top;
} stack_t;


stack_t *push(stack_t *stack, int value)
{
   if (stack->top >= SIZE) {
       LOG_ERROR("Stack over flow!\n");
   }
    stack->top++;
    stack->array[stack->top] = value;
    return stack;
}

int pop(stack_t *stack)
{
   if (stack->top < 0) {
       LOG_ERROR("can't pop from a emtpy stack!\n");
   }
   int result = stack->array[(stack->top)--];
   return result;
}

stack_t *init_stack() {
    stack_t *stack = malloc(sizeof(stack_t));
    stack->top = -1;
    return stack;
}

void print_stack(stack_t *stack)
{
    char *array_value_format;
    printf("[");
    for (int i = stack->top; i >= 0; i--){
        if (i == 0) {
            array_value_format = "%d";
        } else {
            array_value_format = "%d, ";
        }
        printf(array_value_format, stack->array[i]);
    }
    printf("]\n");
}

int main(void)
{
    stack_t *stack = init_stack();
    stack = push(stack, 2);
    stack = push(stack, 5);
    print_stack(stack);
    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack);
    print_stack(stack);
}




