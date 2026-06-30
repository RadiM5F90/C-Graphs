#include <stdio.h>
#include "directed_graph.h"


void print_node_list(const list _list) {
    iterator it = iterator_create(_list);

    while (has_iterator_next(it)) {
        int id = iterator_next(it);
        printf("%d ", id);
    }
    destroy_iterator(&it);
    printf("\n");
}


int main() {
    direct_graph g = direct_graph_create(10);

    node_id a = add_node(g, 10);
    node_id b = add_node(g, 20);
    node_id c = add_node(g, 30);
    node_id d = add_node(g, 40);
    node_id e = add_node(g, 50);


    add_edge(g, a, b);
    add_edge(g, a, c);
    add_edge(g, b, d);
    add_edge(g, c, d);
    add_edge(g, d, e);

    printf("DFS from node %d: ", a);
    list _dfs = direct_graph_dfs(g, a);
    print_node_list(_dfs);
    destroy_list(&_dfs);

    printf("BFS from node %d: ", a);
    list _bfs = direct_graph_bfs(g, a);
    print_node_list(_bfs);
    destroy_list(&_bfs);

    // getting the value
    int value;
    if (get_value(g, d, &value) == 0) printf("\nNode's %d value: %d\n", d, value);


    list neighbors = direct_graph_neighbors(g, b);
    printf("Node's %d neighbors: ", b);
    print_node_list(neighbors);
    destroy_list(&neighbors);

    // checking the path
    printf("path from %d to %d: %s\n", a, e,
        direct_graph_path_exists(g, a, e) ? "Exists" : "Not exists");

    printf("path from %d to %d: %s\n", e, a,
        direct_graph_path_exists(g, e, a) ? "Exists" : "Not exists");

    direct_graph_destroy(&g);

    return 0;
}

