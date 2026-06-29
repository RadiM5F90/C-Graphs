
#include <stdbool.h>
#include <stdlib.h>

#define QUEUE_SUCCESS 0;
#define QUEUE_ERROR_NULL -1;
#define QUEUE_ERROR_ALLOC -2;
#define QUEUE_ERROR_EMPTY -3;
#define QUEUE_ERROR_FULL -4;

typedef struct _queue* queue;

queue queue_create(int _capacity);

void queue_destroy(queue* _q);

int queue_enqueue(queue _q, int _value);

int queue_dequeue(queue _q, int* _value_out);

int queue_peek(queue _q, int* _value_out);

bool queue_is_empty(queue _q);

bool queue_is_full(queue _q);
