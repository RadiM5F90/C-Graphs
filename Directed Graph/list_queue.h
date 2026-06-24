
#include <stdbool.h>

#define QUEUE_SUCCESS 0;
#define QUEUE_ERROR_NULL -1;
#define QUEUE_ERROR_ALLOC -2;
#define QUEUE_ERROR_EMPTY -3;
#define QUEUE_ERROR_FULL -4;

typedef struct _queue *queue;

queue create_queue(int _capacity);

void destroy_queue(queue* _queue);

int enqueue(queue _queue, int _value);

int dequeue(queue _queue, int* _value_out);

int queue_peek(queue _queue, int* _value_out);

bool queue_is_empty(queue _queue);

bool queue_is_full(queue _queue);
