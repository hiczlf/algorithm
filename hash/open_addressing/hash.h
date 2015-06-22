#ifndef HASH_H
#include <stdbool.h>

typedef int element_t;
typedef int position_t;

enum entry_type_t {
    EMPTY,
    LEGITIMATE,
    DELETED,
};

struct hash_entry_t {
    enum entry_type_t type;
    element_t value;

};

struct hash_table_t {
    int table_size;
    int count;
    struct hash_entry_t *entry;
};

int get_next_prime(int);
bool is_prime(int);
int hash(element_t, struct hash_table_t *);
struct hash_table_t *initialize_table(int);
position_t find(element_t, struct hash_table_t *);
void insert(element_t, struct hash_table_t *);
struct hash_table_t * rehash(struct hash_table_t *);
void hash_free(struct hash_table_t *);



#define LOG_ERR(x) \
    fprintf(stderr, x); exit(1);

#endif
