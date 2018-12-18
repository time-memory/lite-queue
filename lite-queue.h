#ifndef _LITE_QUEUE_H_
#define _LITE_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int front;
    int rear;
    int size;
    int element_len;
    pthread_mutex_t mutex;
    char* array;
} lite_queue_t;

extern lite_queue_t* lite_queue_create(int element_len, int queue_size);

extern void lite_queue_destroy(lite_queue_t* queue);

extern int lite_queue_put_item(lite_queue_t* queue, void* item);

extern int lite_queue_get_item(lite_queue_t* queue, void* item);

extern int lite_queue_get_item_counts(lite_queue_t* queue);


#ifdef __cplusplus
}
#endif


#endif
