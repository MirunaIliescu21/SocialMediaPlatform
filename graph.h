#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "queue.h"
#include "linked_list.h"

typedef enum {ALB, NEGRU} color;
#define INF 9999999
#define MAX_QUEUE_SIZE 100

typedef struct list_graph_t list_graph_t;

/**
 * @struct list_graph_t
 * @brief Represents a graph using an adjacency list.
 */
struct list_graph_t
{
	linked_list_t **neighbors; /* Array of linked lists. */
	int nodes; /* Number of nodes in the graph. */
};

/**
 * Compares two integers.
 *
 * @param a - Pointer to the first integer.
 * @param b - Pointer to the second integer.
 * @return The difference between the two integers.
 */
int compare_ints(void *a, void *b);

/**
 * Finds the minimum path between two nodes in a graph using BFS.
 *
 * @param graph - The graph in which to find the path.
 * @param src - The source node.
 * @param dest - The destination node.
 * @return The length of the shortest path, or -1 if no path exists.
 */
int min_path(list_graph_t *graph, int src, int dest);

/**
 * Creates a graph with a specified number of nodes.
 *
 * @param nodes - The number of nodes in the graph.
 * @return A pointer to the created graph.
 */
list_graph_t *lg_create(int nodes);

/**
 * Adds an edge to the graph.
 *
 * @param graph - The graph.
 * @param src - The source node.
 * @param dest - The destination node.
 */
void lg_add_edge(list_graph_t *graph, int src, int dest);

/**
 * Finds a node in the linked list.
 *
 * @param ll - The linked list.
 * @param node - The node data to find.
 * @param pos - Pointer to store the position of the node.
 * @return A pointer to the found node, or NULL if not found.
 */
ll_node_t *find_node(linked_list_t *ll, int node, unsigned int *pos);

/**
 * Checks if an edge exists in the graph.
 *
 * @param graph - The graph.
 * @param src - The source node.
 * @param dest - The destination node.
 * @return 1 if the edge exists, 0 otherwise.
 */
int lg_has_edge(list_graph_t *graph, int src, int dest);

/**
 * Gets the neighbors of a node in the graph.
 *
 * @param graph - The graph.
 * @param node - The node whose neighbors to get.
 * @return A pointer to the linked list of neighbors
 * or NULL if node is invalid.
 */
linked_list_t *lg_get_neighbours(list_graph_t *graph, int node);

/**
 * Removes an edge from the graph.
 *
 * @param graph - The graph.
 * @param src - The source node.
 * @param dest - The destination node.
 */
void lg_remove_edge(list_graph_t *graph, int src, int dest);

/**
 * Frees the memory allocated for the graph.
 *
 * @param graph - The graph.
 */
void lg_free(list_graph_t *graph);

#endif
