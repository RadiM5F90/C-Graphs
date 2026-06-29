#include "list_queue.h"


typedef struct _node {
    int value;
    struct _node *next;
}node;

struct _queue {
    node* head;
    node* tail;
    int capacity;
    int size;
};

queue queue_create(int _capacity) {
    if (_capacity <= 0) return NULL;

    queue q = malloc(sizeof(struct _queue));
    if (q == NULL) return NULL;

    q->head = q->tail = NULL;
    q->capacity = _capacity;
    q->size = 0;

    return q;
}

void queue_destroy(queue* _q) {
    if (_q == NULL || *_q == NULL) return;

    node* current = (*_q)->head;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
    free(*_q);
    *_q = NULL;
}

bool queue_is_empty(queue _q) {
    return (_q == NULL || _q->size == 0);
}

bool queue_is_full(queue _q) {
    if (_q == NULL) return false;
    return (_q->size == _q->capacity);
}

int queue_enqueue(queue _q, int _value) {
    if (_q == NULL) return QUEUE_ERROR_NULL;
    if (queue_is_full(_q)) return QUEUE_ERROR_FULL;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return QUEUE_ERROR_ALLOC;

    new_node->value = _value;
    new_node->next = NULL;

    if (_q->tail == NULL) _q->head = new_node;
    else _q->tail->next = new_node;

    _q->tail = new_node;
    _q->size++;

    return QUEUE_SUCCESS;
}


int queue_dequeue(queue _q, int* _value_out) {
    if (_q == NULL) return QUEUE_ERROR_NULL;
    if (queue_is_empty(_q)) return QUEUE_ERROR_EMPTY;

    node* to_delete = _q->head;
    *_value_out = to_delete->value;
    _q->head = to_delete->next;
    free(to_delete);

    _q->size--;

    if (_q->head == NULL) _q->tail = NULL;

    return QUEUE_SUCCESS;
}


int queue_peek(queue _q, int* _value_out) {
    if (_q == NULL) return QUEUE_ERROR_NULL;
    if (queue_is_empty(_q)) return QUEUE_ERROR_EMPTY;

    *_value_out = _q->head->value;
    return QUEUE_SUCCESS;
}
