#include "linked_list.h"

typedef struct _node {
    int value;
    struct _node* next;
}node;

struct _list {
    node* head;
    node* tail;
    int size;
};

struct _iterator {
    list _list;
    node* current;
};

list list_create(){
    list _list = malloc(sizeof(struct _list));
    if (_list != NULL) {
        _list->head = _list->tail = NULL;
        _list->size = 0;
    }
    return _list;
}

void list_destroy(list* _list) {
    if (_list == NULL || *_list == NULL) return;

    node* current = (*_list)->head;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
    free(*_list);
    *_list = NULL;
}

int list_insert_front(list _list, int value) {
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

int list_insert_back(list _list, int value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return LINKED_LIST_ERROR_ALLOC;

    new_node->value = value;
    new_node->next == NULL;

    if (_list->tail != NULL) _list->tail->next = new_node;
    else _list->head = new_node;

    _list->tail = new_node;
    _list->size++;

    return LINKED_LIST_SUCCESS;
}

int list_insert_at(list _list, int index, int value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (index < 0 || index > _list->size) return LINKED_LIST_ERROR_INDEX;
    if (index == 0) return list_insert_front(_list, value);
    if (index == _list->size) return list_insert_back(_list, value);

    node* prev = _list->head;
    for (int i = 0; i < index - 1; i++) prev = prev->next;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return LINKED_LIST_ERROR_ALLOC;

    new_node->value = value;
    new_node->next = prev->next;
    prev->next = new_node;

    _list->size++;
    return LINKED_LIST_SUCCESS;
}

int list_is_empty(const list _list) {
    return (_list->size == 0);
}

int list_get_front(list _list, int* _value_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (list_is_empty(_list)) return LINKED_LIST_ERROR_EMPTY;

    *_value_out = _list->head->value;
    return LINKED_LIST_SUCCESS;
}

int list_get_back(list _list, int* _value_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (list_is_empty(_list)) return LINKED_LIST_ERROR_EMPTY;

    *_value_out = _list->tail->value;
    return LINKED_LIST_SUCCESS;
}

int list_get_at(list _list, int index, int* _value_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (list_is_empty(_list)) return LINKED_LIST_ERROR_EMPTY;
    if (index < 0 || index > _list->size) return LINKED_LIST_ERROR_INDEX;

    node* current = _list->head;
    for (int i = 0; i < index - 1; i++) current = current->next;

    *_value_out = current->value;
    return LINKED_LIST_SUCCESS;
}

int list_find(list _list, int value, int* _index_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

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

int list_remove_at(list _list, int index) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (list_is_empty(_list)) return LINKED_LIST_ERROR_EMPTY;
    if (index < 0 || index > _list->size) return LINKED_LIST_ERROR_INDEX;

    node* to_delete;
    if (index == 0) {
        to_delete = _list->head;
        _list->head = to_delete->next;
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
    _list->size++;
    return LINKED_LIST_SUCCESS;
}

int list_remove_value(list _list, int value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    if (list_is_empty(_list)) return LINKED_LIST_ERROR_EMPTY;

    node* current = _list->head;
    node* prev = NULL;

    while (current != NULL && current->value != value) {
        prev = current;
        current = current->next;
    }
    if (current == NULL){return LINKED_LIST_ERROR_NOT_FOUND;}

    else {
        if (prev == NULL) {
            _list->head = current->next;
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

int list_size(list _list) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    return _list->size;
}



iterator iterator_create(list _list) {
    if (_list == NULL) return NULL;

    iterator it = malloc(sizeof(struct _iterator));
    if (it == NULL) return NULL;

    it->current = _list->head;
    return it;
}

bool iterator_has_next(iterator _it) {
    return (_it != NULL && _it->current != NULL);
}

int iterator_next(iterator _it) {
    int value = _it->current->value;
    _it->current = _it->current->next;

    return value;
}

void iterator_destroy(iterator* _it) {
    if (_it == NULL || *_it == NULL) return;

    free(*_it);
    *_it = NULL;
}
