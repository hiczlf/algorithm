#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void fatal_error(char *err)
{
    fprintf(stderr, "%s\n", err);
    exit(1);
}

element_type min(element_type a, element_type b)
{
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

struct heap_t *heap_init(int capacity)
{
    struct heap_t *heap;
    heap = malloc(sizeof(struct heap_t));
    if (heap == NULL) {
        fatal_error("out of memory");
    }

    heap->elements = malloc(sizeof(element_type) * (capacity + 1));
    if (heap->elements == NULL) {
        fatal_error("out of memory");
    }

    heap->capacity = capacity;
    heap->size = 0;
    heap->elements[0] = MIN;
    return heap;
}

bool is_full(struct heap_t *heap)
{
    if (heap->size >= heap->capacity) {
        return true;
    } else {
        return false;
    }
}

bool is_empty(struct heap_t *heap)
{
    if (heap->size == 0) {
        return true;
    } else {
        return false;
    }
}


void heap_insert(element_type element,
                 struct heap_t *heap)
{
    int i;

    if (is_full(heap)) {
        fatal_error("heap is full");
    }
    for (i = heap->size+1;
         element < heap->elements[i / 2 ];
         i /=  2
         ) {
        heap->elements[i] = heap->elements[i / 2];
    }
    heap->elements[i] = element;
    heap->size++;
}

element_type delete_min(struct heap_t* heap)
{
    element_type min_element, last_element;
    int i, child;

    if (is_empty(heap)) {
        fatal_error("can't delete_min from empty heap");
    }

    min_element = heap->elements[1];
    last_element = heap->elements[heap->size--];

    for (i = 1; i * 2 <= heap->size; i = child) {
        child = i * 2;
        if (child != heap->size &&
                heap->elements[child] > heap->elements[child + 1]) {
            child++;
        }

        if (last_element > heap->elements[child]) {
            heap->elements[i] = heap->elements[child];
        } else {
            break;
        }
    }

    heap->elements[i] = last_element;
    return min_element;
}

void heap_print(struct heap_t *heap)
{
    for(int i = 1; i <= heap->size; i++) {
        printf("%d ", heap->elements[i]);
    }
    printf("\n");
}

int main(void) {
    struct heap_t *heap;
    heap = heap_init(50);
    heap_insert(1, heap);
    heap_insert(23, heap);
    heap_insert(112, heap);
    heap_insert(2, heap);
    heap_insert(4, heap);
    heap_insert(3, heap);
    heap_print(heap);
    printf("%d\n", delete_min(heap));
    heap_print(heap);
}

