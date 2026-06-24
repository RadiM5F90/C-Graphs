#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// LINKED LISTS
typedef struct _node {
    struct _node* next;
    int value;
}node;

struct _list {
    node* head;
    node* tail;
    int size;
};

struct _list_iterator {
    list _list;
    node* current;
};

list create_list() {
    list _list = malloc(sizeof(struct _list));
    if (_list != NULL) {
        _list->head = _list->tail = NULL;
        _list->size = 0;
    }
    return _list;
}

int insert_front(list _list, int value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return LINKED_LIST_ERROR_ALLOC;

    new_node->value = value;
    new_node->next = _list->head;
    _list->head = new_node;

    if (_list->tail == NULL) _list->tail = new_node;
    _list->size++;

    return LINKED_LIST_SUCCESS;
}

int insert_back(list _list, int value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return LINKED_LIST_ERROR_ALLOC;

    new_node->value = value;
    new_node->next = NULL;

    if (_list->tail != NULL) _list->tail->next = new_node;
    else _list->head = new_node;

    _list->tail = new_node;
    _list->size++;
    return LINKED_LIST_SUCCESS;
}

int insert_at(list _list, int index, int value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (index < 0 || index > _list->size) return LINKED_LIST_ERROR_INDEX;
    if (index == 0) return insert_front(_list, value);
    if (index == _list->size - 1) return insert_back(_list, value);


    node* prev = _list->head;
    for (int i = 0; i < index - 1 ; i++) prev = prev->next;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return LINKED_LIST_ERROR_ALLOC;

    new_node->value = value;
    new_node = prev->next;
    prev->next = new_node;

    _list->size++;
    return LINKED_LIST_SUCCESS;
}

bool list_is_empty(list _list) {
    return (_list == NULL || _list->size == 0);
}

int get_front(list _list, int* _value_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (list_is_empty(_list)) return LINKED_LIST_ERROR_EMPTY;

    *_value_out = _list->head->value;

    return LINKED_LIST_SUCCESS;
}

int get_back(list _list, int* _value_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (list_is_empty(_list)) return LINKED_LIST_ERROR_EMPTY;

    *_value_out = _list->tail->value;

    return LINKED_LIST_SUCCESS;
}
int get_at(list _list, int index, int* _value_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (index < 0 || index > _list->size) return LINKED_LIST_ERROR_INDEX;
    if (index == 0) return get_front(_list, _value_out);
    if (index == _list->size - 1) return get_back(_list, _value_out);

    node* current = _list->head;
    for (int i = 0; i < index; i++) current = current->next;

    *_value_out = current->value;

    return LINKED_LIST_SUCCESS;
}

int list_find(list _list, int value, int* _index_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (list_is_empty(_list)) return LINKED_LIST_ERROR_EMPTY;

    node* current = _list->head;
    int index = 0;

    while (current != NULL && current->value != value) {
        current = current->next;
        index++;
    }
    if (current == NULL) {return LINKED_LIST_ERROR_NOT_FOUND;}
    else {
        *_index_out = index;
        return LINKED_LIST_SUCCESS;
    }
}

int remove_value(list _list, int value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (list_is_empty(_list)) return LINKED_LIST_ERROR_EMPTY;

    node* current = _list->head;
    node* prev = NULL;

    // move the pointers forward
    while (current != NULL && current->value != value) {
        prev = current;
        current = current->next;
    }
    // if current is NULL it means that the value was not found
    if (current == NULL) {return LINKED_LIST_ERROR_NOT_FOUND;}

    else {
        // if prev is NULL it means that the value is the _list->head->value
        if (prev == NULL) {
            _list->head = current->next;
            // if it was the only element in the list, set both head and tail to NULL
            if (_list->head == NULL) _list->tail = NULL;
        }
        else {
            prev->next = current->next;
            if (current == _list->tail) _list->tail = prev;
        }
        free(current);
        _list->size--;
        return LINKED_LIST_SUCCESS;
    }
}

int remove_at(list _list, int index) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (index < 0 || index > _list->size) return LINKED_LIST_ERROR_INDEX;
    if (list_is_empty(_list)) return LINKED_LIST_ERROR_EMPTY;

    node* to_delete;

    if (index == 0) {
        to_delete = _list->head;
        _list->head = _list->head->next;
        if (_list->head == NULL) _list->tail = NULL;
    }
    else {
        node* prev = _list->head;

        for (int i = 0; i < index - 1; i++) prev = prev->next;
        to_delete = prev->next;
        prev->next = to_delete->next;
        if (to_delete == _list->tail) _list->tail = prev;
    }
    free(to_delete);
    _list->size--;
    return LINKED_LIST_SUCCESS;
}

int list_size(list _list) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    return _list->size;
}

void destroy_list(list* _list) {
    if (_list == NULL) return;

    node* current = (*_list)->head;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
    free(*_list);
    *_list = NULL;
}


// ITERATOR
iterator iterator_create(list _list) {
    if (_list == NULL) return NULL;

    iterator _iterator = malloc(sizeof(struct _list_iterator));
    if (_iterator == NULL) return NULL;

    _iterator->current = _list->head;

    return _iterator;
}

bool has_iterator_next(iterator _iterator) {
    return _iterator != NULL && _iterator->current != NULL;
}

int iterator_next(iterator _iterator) {
    int value = _iterator->current->value;
    _iterator->current = _iterator->current->next;
    return value;
}

void destroy_iterator(iterator* _iterator) {
    if (_iterator == NULL || *_iterator == NULL) return;
    free(*_iterator);
    *_iterator = NULL;
}
