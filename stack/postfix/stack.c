/*
 * Reverse Polish notation 计算器
 * normal notation: 5 + ((1 + 2) × 4) − 3
 * 等于: 5 1 2 + 4 × + 3 −
 *
 * 示例: ./stack '1 23 123 + ='
 * 数字和操作符必须用空格分开, 发现分析算数公式也是蛮麻烦的, 就没有实现了
 */
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* 根据操作符进行运算
 * result 等于 stack倒数第二个值 operator stack末尾的值
 * 然后把result push到stack中, 进行下一次运算
 */
int calc(stack_t *number_stack, char operator)
{
    int result;
    int first_operand, second_operand;
    char err_str[100];
    second_operand = pop(number_stack);
    first_operand = pop(number_stack);
    switch (operator) {
        case '+':
            result = first_operand + second_operand;
            break;
        case '-':
            result = first_operand - second_operand;
            break;
        case '*':
            result = first_operand * second_operand;
            break;
        case '/':
            result = first_operand / second_operand;
            break;
        default:
            sprintf(err_str, "unrecongnized operator: %c\n", operator);
            LOG_ERROR(err_str);
            exit(1);
    }
    push(number_stack, result);
    return result;
}

int main(int argc, char **argv)
{
    char *token;
    char *ptr;
    char formula[200];
    int number, result;
    stack_t * number_stack = init_stack();

    if (argc < 2) {
        fprintf(stderr, "Usage: 'arithmetic formula'\n");
        exit(0);
    }

    strcpy(formula, argv[1]);
    token = strtok(formula, " ");
    /* 计算结果 */
    while (token != NULL) {
        number = (int) strtol(token, &ptr, 10);
        /* 如果是数字, 则放到栈中 */
        if (*ptr == '\0') {
            push(number_stack, number);
        /* 否则认为是运算符, 进行计算 */
        } else {
            printf("operator is %s\n", token);
            result = calc(number_stack, token[0]);
        }
        token = strtok(NULL, " ");
    }

    /* 输出计算结果 */
    printf("%s = %d\n", argv[1], result);
}
