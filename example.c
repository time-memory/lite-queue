#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "lite-queue.h"

typedef struct
{
    int index;
    int value;
    char note[32];
} item_t;

static char strings[] = "Spending your money for charity can buy eternal happiness for you as well as the person you helped .";

int main(void)
{
	lite_queue_t* queue = NULL;
    item_t item;
    char* p = strings;
    char* q = NULL;
    int i = 0;

    srand(time(NULL));
    queue = lite_queue_create(sizeof(item_t), 20);
    if (NULL == queue)
    {
        printf("create lite queue failed.\n");
        return -1;
    }

    for (i = 0; i < 18; i++)
    {
        memset(&item, 0, sizeof(item));
        item.index = i;
        item.value = rand() % 1024;
        q = strchr(p, ' ');
        strncpy(item.note, p, q-p);
        lite_queue_put_item(queue, &item);
        p = q + 1;
    }

    printf("item counts : %d\n", lite_queue_get_item_counts(queue));

    for (i = 0; i < 18; i++)
    {
        memset(&item, 0, sizeof(item));
        lite_queue_get_item(queue, &item);
        printf("[%02d] index : %02d, value : %4d, note : %s\n", i, item.index, item.value, item.note);
    }

    printf("item counts : %d\n", lite_queue_get_item_counts(queue));
    lite_queue_destroy(queue);

    return 0;
}
