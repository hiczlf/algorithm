#include <stdio.h>
#include <stdarg.h>

void testit (int i, ...)
{
    va_list argptr;
    va_start(argptr, i);

    if (i == 0)
    {
        int n = va_arg(argptr, int);
        printf("%d\n", n);
    }
    else
    {
        int c = va_arg(argptr, char*);
        printf("%d\n", c);
    }
}

int main()
{
    testit(0, 232, 23); /* 1st problem: 0xffffffff is not an int */
    testit(1, 'a', 'b');       /* 2nd problem: NULL is not a char* */
}
