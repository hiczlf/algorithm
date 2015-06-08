#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hash.h"
#include "log.h"

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

node_t *list_find(struct list_t *list, element_t value) {
    node_t *node;
    node = list->next;
    while (node) {
        if (node->value == value) {
            return node;
        }
        node = node->next;
    }
    return node;
}

struct hash_t *hash_init(int table_size)
{
    struct hash_t *hash = malloc(sizeof(struct hash_t));
    if (table_size < MIN_TABLE_SIZE)  {
        LOG_ERROR("Error: Too small hash table size\n");
        exit(1);
    }

    hash->size = get_next_prime(table_size);
    hash->hash_table = malloc(sizeof(struct list_t) * hash->size);
    for (int i = 0; i < hash->size; i++) {
        hash->hash_table[i] = malloc(sizeof(struct list_t));
        if (hash->hash_table[i] == NULL) {
            LOG_ERROR("Error: Out of space");
            exit(1);
        } else {
            hash->hash_table[i]->next = NULL;
        }
    }
    return hash;
}

int _hash(element_t value, int table_size) {
    return value % table_size;
}

node_t *hash_find(element_t value, struct hash_t *hash) {
    struct list_t *position;
    node_t * node;
    int hash_value = _hash(value, hash->size);
    position = hash->hash_table[hash_value];
    node = list_find(position, value);
    return node;
}

void hash_insert(element_t value, struct hash_t *hash) {
    struct list_t *position;
    node_t *node, *new_node;

    int hash_value = _hash(value, hash->size);
    position = hash->hash_table[hash_value];
    node = list_find(position, value);
    if (!node) {
        new_node = malloc(sizeof(node_t));
        if (new_node) {
            new_node->next = position->next;
            new_node->value = value;
            position->next = new_node;
        } else {
            LOG_ERROR("Error: Out of space!\n");
            exit(1);
        }
    }
}

void hash_delete(element_t value, struct hash_t *hash) {
    struct list_t *position;
    node_t *node_prev, *node;
    int hash_value = _hash(value, hash->size);
    position = hash->hash_table[hash_value];

    node_prev = position;
    node = position->next;
    while(node) {
        if (node->value == value) {
            node_prev->next = node->next;
            free(node);
        }
        node_prev = node;
        node = node->next;
    }
}

void hash_print(struct hash_t *hash)
{
    node_t *node;
    for (int i = 0; i < hash->size; i++) {
        node = hash->hash_table[i]->next;
        while(node) {
            printf(" %d", node->value);
            node = node->next;
        }
        printf("\n");
    }
}

int main(void) {
    struct hash_t *hash;
    node_t *node;
    int length = 1000 * 10000;
    hash = hash_init(length);
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        hash_insert(i, hash);
    }
    for (int i = 0; i < length; i++) {
        node = hash_find(i, hash);
        if (node) {
            printf("%d\n", node->value);
        }
    }
}
