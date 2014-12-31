#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 256

void parser_poly(char *);

void parse_poly(char *poly_str) {
    int i, term_length;
    char *chr, *term_begin;
    char *terms[100] = { NULL };


    chr = poly_str;
    term_begin = poly_str;

    i = 0;
    while (*chr != '\0') {
        if (*chr == '-' || *chr == '+') {
            term_length = chr - term_begin + 1;
            terms[i] = (char *)malloc(term_length);
            strncpy(terms[i], chr, term_length);
            terms[i][term_length] = '\0';
            i++;
        }

        chr++;
    }

    i = 0;
    while (terms[i] != NULL) {
        printf("term is: %s\n", terms[i]);
        i++;
    }

}

int main(int argc, char **argv)
{
    char *poly;

    if (argc < 2) {
        fprintf(stderr, "Usage like: %s '2x + 3x * 34x^2'\n", argv[0]);
        exit(1);
    }
    poly = argv[1];

    parse_poly(poly);
    exit(0);
}
