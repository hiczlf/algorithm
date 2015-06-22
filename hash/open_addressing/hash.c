#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "hash.h"

#define MIN_HASH_TABLE_SIZE  5


bool is_prime(int number) {
    if (number <= 1) {
        return false;
    }

    for(int i = 2; i < number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

/* 获取下一个质数 */
int get_next_prime(int start)
{
    while (true) {
        if (is_prime(start)) {
            break;
        }
        start++;
    }
    return start;
}

int hash(element_t value, struct hash_table_t *hash_table)
{
    return value % hash_table->table_size;
}


struct hash_table_t *initialize_table(int table_size)
{
    if (table_size < MIN_HASH_TABLE_SIZE) {
        LOG_ERR("table_size too small\n");
    }

    struct hash_table_t * hash_table;
    hash_table = malloc(16);
    if (!hash_table) {
        LOG_ERR("out of space\n");
    }

    hash_table->table_size = get_next_prime(table_size);

    struct hash_entry_t *entry = malloc(
            sizeof(struct hash_entry_t) * hash_table->table_size);

    if (!entry) {
        LOG_ERR("out of space\n");
    }

    for (int i = 0; i < hash_table->table_size; i++) {
        entry[i].type = EMPTY;
    }
    hash_table->entry = entry;
    hash_table->count = 0;

    return hash_table;
}

position_t find(element_t value, struct hash_table_t *hash_table)
{
    int position;
    int collision_num = 0;

    position = hash(value, hash_table);

    while(hash_table->entry[position].type !=  EMPTY &&
            hash_table->entry[position].value != value) {

        position += 2 * ++collision_num - 1;

        if (position >= hash_table->table_size) {
            position -= hash_table->table_size;
        }
    }
    return position;
}

void insert(element_t value, struct hash_table_t *hash_table)
{
    position_t position;
    position = find(value, hash_table);
    if (hash_table->entry[position].type != LEGITIMATE) {
        hash_table->entry[position].value = value;
        hash_table->entry[position].type = LEGITIMATE;
        hash_table->count++;
    }

    if (hash_table->count > hash_table->table_size / 2) {
        rehash(hash_table);
    }
}

struct hash_table_t *rehash(struct hash_table_t *hash_table)
{
    struct hash_table_t *tmp_hash_table;
    struct hash_entry_t hash_entry;

    tmp_hash_table = initialize_table(hash_table->table_size * 2);

    for (int i = 0; i < hash_table->table_size; i++) {
        hash_entry = hash_table->entry[i];
        if (hash_entry.type == LEGITIMATE) {
            insert(hash_entry.value, tmp_hash_table);
        }
    }


    hash_table->table_size = tmp_hash_table->table_size;

    free(hash_table->entry);
    hash_table->entry = tmp_hash_table->entry;

    free(tmp_hash_table);
    return hash_table;
}

void hash_free(struct hash_table_t *hash_table)
{
    free(hash_table->entry);
    free(hash_table);
}

int main(void) {
    position_t position;
    struct hash_table_t *hash_table;
    int length = 1000 * 10000;

    hash_table = initialize_table(10005);

    for (int i = 0; i < length; i++) {
        insert(i, hash_table);
    }

    for (int i = 0; i < length; i++) {
        position = find(i, hash_table);
        if (hash_table->entry[position].type != LEGITIMATE) {
            printf("Error\n");
        }
    }
    hash_free(hash_table);
}
