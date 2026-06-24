
#include "linked_list.h"


/*
 * struct for the graph and a typedef int for the node id
 * create and destroy the graph
 * node_id add_node
 * get the value
 * add and remove an edge, check the size of the graph
 * check if 2 nodes are adjacent, check if a path exists between 2 nodes
 *
 * bfs and dfs using linked lists, and check for a node's neighbor
 */

#define DIRECT_GRAPH_SUCCESS 0;
#define DIRECT_GRAPH_ERROR_NULL -1;
#define DIRECT_GRAPH_ERROR_INVALID_ID -2;
#define DIRECT_GRAPH_ERROR_MEMORY -3;

typedef struct _direct_graph* direct_graph;
typedef int node_id;

direct_graph direct_graph_create(int _max_size);

void direct_graph_destroy(direct_graph* _graph);

node_id add_node(direct_graph _graph, int value);

int get_value(direct_graph _graph, node_id _node, int* _value_out);

int add_edge(direct_graph _graph, node_id _src, node_id _dst);

int remove_edge(direct_graph _graph, node_id _src, node_id _dst);

int direct_graph_size(direct_graph _graph);

int direct_graph_adjacent(direct_graph _graph, node_id _src, node_id _dst);

int direct_graph_path_exists(direct_graph _graph, node_id _src, node_id _dst);


list direct_graph_neighbors(direct_graph _graph, node_id _node);

list direct_graph_dfs(direct_graph _graph, node_id _start);

list direct_graph_bfs(direct_graph _graph, node_id _start);

