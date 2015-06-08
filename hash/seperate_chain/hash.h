#ifndef HASH_H

#include <stdbool.h>
#define MIN_TABLE_SIZE 10

typedef int element_t;

typedef struct list_t node_t;

struct list_t {
    int  value;
    node_t *next;
};



struct hash_t {
    int size;
    struct list_t **hash_table;
};


struct hash_t * hash_init(int table_size);
node_t *hash_find(element_t, struct hash_t *);
void hash_insert(element_t, struct hash_t *);

#endif
