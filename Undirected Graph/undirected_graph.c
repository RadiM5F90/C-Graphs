#include "undirected_graph.h"
#include "list_stack.h"
#include "list_queue.h"


// TMATRIX -> triangular matrix
#define TMATRIX_SIZE(n) ((n) * ((n) + 1) / 2)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


struct _indirect_graph {
    int* nodes;
    int* edges;
    int size;
    int max_size;
};

int tmatrix_index(int i, int j);


indirect_graph indirect_graph_create(int max_size) {
    if (max_size <= 0) return NULL;

    indirect_graph _g = malloc(sizeof(struct _indirect_graph));
    if (_g == NULL) return NULL;

    _g->nodes = malloc(sizeof(int) * max_size);
    if (_g->nodes == NULL) {
        free(_g);
        return NULL;
    }

    _g->edges = calloc(TMATRIX_SIZE(max_size), sizeof(int));
    if (_g->edges == NULL) {
        free(_g->edges);
        free(_g);
        return NULL;
    }

    _g->size = 0;
    _g->max_size = max_size;
    return _g;
}


void indirect_graph_destroy(indirect_graph* _g) {
    if (_g == NULL || *_g == NULL) return;
    free(*_g);
    *_g = NULL;
}


node_id add_node(indirect_graph _g, int _value) {
    if (_g == NULL) return INDIRECT_GRAPH_ERROR_NULL;
    if (_g->size == _g->max_size) return INDIRECT_GRAPH_ERROR_MEMORY;

    node_id new_node_id = _g->size;
    _g->nodes[new_node_id] = _value;
    _g->size++;

    return new_node_id;
}


int indirect_graph_get_value(indirect_graph _g, node_id _node, int* _value_out) {
    if (_g == NULL) return INDIRECT_GRAPH_ERROR_NULL;
    if (_node < 0 ||_node  >= _g->size) return INDIRECT_GRAPH_ERROR_INVALID_ID;

    *_value_out = _g->nodes[_node];
    return INDIRECT_GRAPH_SUCCESS;
}


int add_edge(indirect_graph _g, node_id _src, node_id _dst) {
    if (_g == NULL) return INDIRECT_GRAPH_ERROR_NULL;
    if (_src < 0 || _src >= _g->size || _dst < 0 || _dst >= _g->size) return INDIRECT_GRAPH_ERROR_INVALID_ID;

    _g->edges[tmatrix_index(_src, _dst)] = 1;
    return INDIRECT_GRAPH_SUCCESS;
}


int remove_edge(indirect_graph _g, node_id _src, node_id _dst) {
    if (_g == NULL) return INDIRECT_GRAPH_ERROR_NULL;
    if (_src < 0 || _src >= _g->size || _dst < 0 || _dst >= _g->size) return INDIRECT_GRAPH_ERROR_INVALID_ID;

    _g->edges[tmatrix_index(_src, _dst)] = 0;
    return INDIRECT_GRAPH_SUCCESS;
}


int indirect_graph_size(indirect_graph _g) {
    if (_g == NULL) return INDIRECT_GRAPH_ERROR_NULL;
    return _g->size;
}


int indirect_graph_adjacent(indirect_graph _g, node_id _src, node_id _dst) {
    if (_g == NULL) return INDIRECT_GRAPH_ERROR_NULL;
    if (_src < 0 || _src >= _g->size || _dst < 0 || _dst >= _g->size) return INDIRECT_GRAPH_ERROR_INVALID_ID;

    return _g->edges[tmatrix_index(_src, _dst)];
}


list indirect_graph_neighbors(indirect_graph _g, node_id _node) {
    if (_g == NULL || _node < 0 || _node >= _g->size) return NULL;

    list _list = list_create();

    for (int i = 0; i < _g->size; i++) {
        if (_g->edges[tmatrix_index(_node, i)] == 1) list_insert_back(_list, i);
    }
    return _list;
}


list indirect_graph_dfs(indirect_graph _g, node_id _start) {
    if (_g == NULL || _start < 0 || _start >= _g->size) return NULL;

    bool* visited = calloc(_g->size, sizeof(bool));
    list result = list_create();
    stack s = stack_create(_g->size);

    stack_push(s, _start);
    while (!stack_is_empty(s)) {
        int current;
        stack_pop(s, &current);

        if (!visited[current]) {
            visited[current] = true;

            list_insert_back(result, current);

            list neighbors = indirect_graph_neighbors(_g, current);
            iterator it = iterator_create(neighbors);

            while (iterator_has_next(it)) {
                int neighbor = iterator_next(it);
                stack_push(s, neighbor);
            }
            iterator_destroy(&it);
            list_destroy(&neighbors);
        }
    }
    stack_destroy(&s);
    free(visited);
    return result;
}


list indirect_graph_bfs(indirect_graph _g, node_id _start) {
    if (_g == NULL || _start < 0 || _start >= _g->size) return NULL;

    bool* visited = calloc(_g->size, sizeof(bool));
    list result = list_create();
    queue q = queue_create(_g->size);

    queue_enqueue(q, _start);
    while (!queue_is_empty(q)) {
        int current;
        queue_dequeue(q, &current);

        if (!visited[current]) {
            visited[current] = true;
            list_insert_back(result, current);

            list neighbors = indirect_graph_neighbors(_g, current);
            iterator it = iterator_create(neighbors);

            while (iterator_has_next(it)) {
                int neighbor = iterator_next(it);
                queue_enqueue(q, neighbor);
            }
            iterator_destroy(&it);
            list_destroy(&neighbors);
        }
    }
    queue_destroy(&q);
    free(visited);
    return result;
}


int indirect_graph_path_exists(indirect_graph _g, node_id _src, node_id _dst) {
    if (_g == NULL) return INDIRECT_GRAPH_ERROR_NULL;
    if (_src < 0 || _src >= _g->size || _dst < 0 || _dst >= _g->size) return INDIRECT_GRAPH_ERROR_INVALID_ID;

    bool* visited = calloc(_g->size, sizeof(bool));
    stack s = stack_create(_g->size);
    bool found = false;

    stack_push(s, _src);
    while (!stack_is_empty(s) && !found) {
        int current;
        stack_pop(s, &current);

        if (!visited[current]) {
            if (current == _dst) found = true;
            else {
                visited[current] = true;

                list neighbors = indirect_graph_neighbors(_g, current);
                iterator it = iterator_create(neighbors);

                while (iterator_has_next(it)) {
                    int neighbor = iterator_next(it);
                    stack_push(s, neighbor);
                }
                iterator_destroy(&it);
                list_destroy(&neighbors);
            }
        }
    }
    stack_destroy(&s);
    free(visited);
    return found;
}


int tmatrix_index(int i, int j) {
    int row = MAX(i, j);
    int col = MIN(i, j);
    return (row * (row + 1)) / 2 + col;
}
