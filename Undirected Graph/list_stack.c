#include "list_stack.h"

typedef struct _node {
    int value;
    struct _node* next;
}node;

struct _stack {
    node* top;
    int size;
    int capacity;
};

stack stack_create(int _capacity) {
    if (_capacity <= 0) return NULL;

    stack s = malloc(sizeof(struct _stack));
    if (s == NULL) return NULL;

    s->top = NULL;
    s->capacity = _capacity;
    s->size = 0;

    return s;
}

void stack_destroy(stack* _s) {
    if (_s == NULL) return;

    node* current = (*_s)->top;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
    free(*_s);
    *_s = NULL;
}

bool stack_is_empty(stack _s) {
    return (_s == NULL || _s->size == 0);
}

bool stack_is_full(stack _s) {
    if (_s == NULL) return false;
    return(_s->size == _s->capacity);
}

int stack_push(stack _s, int _value) {
    if (_s == NULL) return STACK_ERROR_NULL;
    if (stack_is_full(_s)) return STACK_ERROR_FULL;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return STACK_ERROR_ALLOC;

    new_node->value = _value;
    new_node->next = _s->top;
    _s->top = new_node;
    _s->size++;

    return STACK_SUCCESS;
}

int stack_pop(stack _s, int* _value_out) {
    if (_s == NULL) return STACK_ERROR_NULL;
    if (stack_is_empty(_s)) return STACK_ERROR_EMPTY;

    node* to_delete = _s->top;
    *_value_out = to_delete->value;
    _s->top = to_delete->next;

    free(to_delete);
    _s->size--;
    return STACK_SUCCESS;
}

int stack_top(stack _s, int* _value_out) {
    if (_s == NULL) return STACK_ERROR_NULL;
    if (stack_is_empty(_s)) return STACK_ERROR_EMPTY;

    *_value_out = _s->top->value;
    return STACK_SUCCESS;
}
