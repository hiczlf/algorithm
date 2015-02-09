/*
 * array 实现queue
 */

#include <stdio.h>
#include <stdlib.h>
#include "log.h"

struct queue_record {
    unsigned int q_max_size;
    unsigned int q_front;
    unsigned int q_rear;
    unsigned int q_size;
    int *q_array;
};

typedef struct queue_record * queue_t;

/* 初始化queue, 一开始q_rear 比 q_front 小1 */
queue_t init_queue(int q_max_size)
{
    queue_t queue = malloc(sizeof(struct queue_record));
    queue->q_max_size = q_max_size;
    queue->q_front = 1;
    queue->q_rear = 0;
    queue->q_size = 0;
    queue->q_array = malloc(sizeof(int) * q_max_size);
    return queue;
}

void print_queue(queue_t queue)
{
    int q_idx;
    printf("[");
    for (unsigned int i  = 0; i < queue->q_size; i++) {
        q_idx = (queue->q_front + i) % queue->q_max_size;
        printf("%d", queue->q_array[q_idx]);
        if (i != queue->q_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int is_full(queue_t queue){
    if (queue->q_size  >= queue->q_max_size) {
        return 1;
    } else {
        return 0;
    }
}

int is_empty(queue_t queue){
    if (queue->q_size == 0) {
        return 1;
    } else {
        return 0;
    }
}

queue_t enqueue(queue_t queue, int value)
{
    if (is_full(queue) == 1) {
        LOG_ERROR("Can't enqueue to a full queue\n");
        exit(1);
    }

    queue->q_rear = (queue->q_rear + 1) % (queue->q_max_size);
    queue->q_array[queue->q_rear] = value;
    (queue->q_size)++;
    return queue;
}

int dequeue(queue_t queue)
{
    int q_idx;
    if (is_empty(queue) == 1) {
        LOG_ERROR("Can't dequeue from a empty queue\n");
        exit(1);
    }

    (queue->q_size)--;
    q_idx = queue->q_front;
    queue->q_front = (queue->q_front + 1) % queue->q_max_size;
    return queue->q_array[q_idx];
}

int main(void) {
    queue_t queue = init_queue(10);
    for (int i = 0; i < 10; i++) {
        enqueue(queue, i);
    }
    print_queue(queue);
}
