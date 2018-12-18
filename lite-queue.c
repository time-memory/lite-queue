#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "lite-queue.h"

static int queue_is_empty(lite_queue_t* queue)
{
    return (queue->rear == queue->front) ? 1:0;
}

static int queue_is_full(lite_queue_t* queue)
{
    return ((queue->rear + 1) % queue->size == queue->front) ? 1 : 0;
}

lite_queue_t* lite_queue_create(int element_len, int queue_size)
{
    lite_queue_t* queue = NULL;

    queue = (lite_queue_t*)malloc(sizeof(lite_queue_t));
    if (NULL == queue)
    {
        printf("malloc queue failed.\n");
        return NULL;
    }

    memset(queue, 0, sizeof(lite_queue_t));
    queue->array = (char*)malloc(element_len*queue_size);
    if (NULL == queue->array)
    {
        printf("malloc queue buffer failed.\n");
        free(queue);
        return NULL;
    }

    queue->size = queue_size;
    queue->element_len = element_len;
    pthread_mutex_init( &queue->mutex, NULL);

    return queue;
}

void lite_queue_destroy(lite_queue_t* queue)
{
    if (queue->array)
    {
        free(queue->array);
        queue->array = NULL;
    }
    pthread_mutex_destroy(&queue->mutex);

    free(queue);
}

int lite_queue_put_item(lite_queue_t* queue, void* item)
{
    pthread_mutex_lock(&queue->mutex);
    if (queue_is_full(queue))
    {
        printf("queue is full, put failed.\n");
        pthread_mutex_unlock(&queue->mutex);
        return -1;
    }

    memcpy(queue->array + (queue->rear * queue->element_len), item, queue->element_len);
    queue->rear = (queue->rear + 1) % queue->size;
    pthread_mutex_unlock(&queue->mutex);

    return 0;
}

int lite_queue_get_item(lite_queue_t* queue, void* item)
{
    pthread_mutex_lock(&queue->mutex);
    if (queue_is_empty(queue))
    {
        printf("queue is empty, get failed.\n");
        pthread_mutex_unlock(&queue->mutex);
        return -1;
    }

    memcpy(item, queue->array + (queue->front * queue->element_len), queue->element_len);
    queue->front = (queue->front + 1) % queue->size;
    pthread_mutex_unlock(&queue->mutex);

    return 0;
}

int lite_queue_get_item_counts(lite_queue_t* queue)
{
    int counts = 0;

    pthread_mutex_lock(&queue->mutex);
    counts = (queue->rear - queue->front >= 0) ? queue->rear - queue->front : queue->rear - queue->front + queue->size;
    pthread_mutex_unlock(&queue->mutex);

    return counts;
}
