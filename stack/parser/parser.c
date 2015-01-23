/*
 * 简单语法错误分析
 * 检查c语言[], (), <>, "", '', {}, 符号不匹配问题
 *
 */
#include <stdio.h>
#include <string.h>
#include "log.h"


#define MARKS "[]()<>{}"
#define OPEN_MARKS "[({<"
#define QUOTES "'\"'"
#define CLOSE_MARKS "])}>"

#define STACK_SIZE 5000
#define ERROR_STR_SIZE 512

typedef char element_type;

typedef struct _stack_t {
    element_type array[STACK_SIZE];
    int top;
} stack_t;


stack_t *push(stack_t *stack, element_type value)
{
   if (stack->top >= STACK_SIZE) {
       LOG_ERROR("Stack over flow!\n");
   }
    stack->top++;
    stack->array[stack->top] = value;
    return stack;
}

element_type pop(stack_t *stack)
{
   if (stack->top < 0) {
       LOG_ERROR("can't pop from a emtpy stack!\n");
   }
   element_type result = stack->array[(stack->top)--];
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
            array_value_format = "%c";
        } else {
            array_value_format = "%c, ";
        }
        printf(array_value_format, stack->array[i]);
    }
    printf("]\n");
}

int parse(char *source_file)
{
    char c;
    char open_mark, stack_head;
    char error_str[ERROR_STR_SIZE];
    stack_t *stack = init_stack();
    FILE *fp = fopen(source_file, "r");

    while ((c = getc(fp)) != EOF) {

        stack_head = stack->array[stack->top];
        switch(c) {
                switch(stack_head) {
                    case '"':
                        pop(stack);
                        break;
                    case '\\':
                        continue;
                }

        }

        stack_head = stack->array[stack->top];

        if (strchr(QUOTES, stack_head) != NULL) {

            if (c == '\\') {
                push(stack, c);
            }
            if (stack_head == '\\') {
                pop(stack);
                continue;
            }

            if (strchr(QUOTES, c) != NULL) {
                pop(stack);
            }
        }
            continue;
        }

        if (strchr(OPEN_MARKS, c) != NULL) {
            push(stack, c);
        } else if (strchr(CLOSE_MARKS, c) != NULL) {
            open_mark = pop(stack);
            if (open_mark != c) {
                snprintf(error_str, ERROR_STR_SIZE, "%c is not matched\n", c);
                LOG_ERROR(error_str);
            }
        }
    }
    return 0;
}



int main(int argc, char **argv)
{
    char *source_file;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s c_file\n", argv[0]);
        exit(1);
    }

    source_file = argv[1];
    parse(source_file);
}
