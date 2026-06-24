#include <stdbool.h>


// LINKED LISTS

#define LINKED_LIST_SUCCESS 0
#define LINKED_LIST_ERROR_NULL -1
#define LINKED_LIST_ERROR_ALLOC -2
#define LINKED_LIST_ERROR_EMPTY -3
#define LINKED_LIST_ERROR_INDEX -4
#define LINKED_LIST_ERROR_NOT_FOUND -5

typedef struct _list* list;
typedef struct _list_iterator* iterator;

list create_list();

int insert_front(list _list, int value);

int insert_back(list _list, int value);

int insert_at(list _list, int index, int value);

int get_front(list _list, int* _value_out);

int get_back(list _list, int* _value_out);

int get_at(list _list, int index, int* _value_out);

int list_find(list _list, int value, int* _index_out);

int remove_value(list _list, int value);

int remove_at(list _list, int index);

int list_size(list _list);

bool list_is_empty(list _list);

void destroy_list(list* _list);


iterator iterator_create(list _list);

bool has_iterator_next(iterator _iterator);

int iterator_next(iterator _iterator);

void destroy_iterator(iterator* _iterator);
