#ifndef HEAP_H

#include <stdbool.h>

#define  MIN -100;
typedef int element_type;

struct heap_t {
    element_type *elements;
    int capacity;
    int size;
};

struct heap_t *heap_init(int capacity);
void heap_insert(element_type, struct heap_t *);
bool is_full(struct heap_t *);
void print_heap(struct heap_t*);
element_type min(element_type, element_type);
element_type delete_min(struct heap_t*);


#endif
