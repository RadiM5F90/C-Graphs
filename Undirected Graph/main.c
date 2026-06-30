#include <stdio.h>
#include "undirected_graph.h"


void print_node_list(const list _list) {
    iterator it = iterator_create(_list);
    while (iterator_has_next(it)) {
        int id = iterator_next(it);
        printf("%d ", id);
    }
    iterator_destroy(&it);
    printf("\n");
}

int main() {
    indirect_graph g = indirect_graph_create(100);

    int a = add_node(g, 10);
    int b = add_node(g, 20);
    int c = add_node(g, 30);
    int d = add_node(g, 40);
    int e = add_node(g, 50);

    add_edge(g, a, b);
    add_edge(g, a, c);
    add_edge(g, b, d);
    add_edge(g, c, d);
    add_edge(g, d, e);

    printf("DFS from node %d: ", a);
    list dfs = indirect_graph_dfs(g, a);
    print_node_list(dfs);
    list_destroy(&dfs);

    printf("BFS from node %d: ", a);
    list bfs = indirect_graph_bfs(g, a);
    print_node_list(bfs);
    list_destroy(&bfs);


    int value;
    if (indirect_graph_get_value(g, d, &value) == 0) printf("Node's %d value: %d\n", d, value);

    list neighbors = indirect_graph_neighbors(g, b);
    printf("Node's %d neighbors: ", b);
    print_node_list(neighbors);
    list_destroy(&neighbors);

    printf("Path from %d to %d: %s\n", a, e, indirect_graph_path_exists(g, a, e) ? "Exists" : "Does not exist");

    indirect_graph_destroy(&g);

    return 0;
}
