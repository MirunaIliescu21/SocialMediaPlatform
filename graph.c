#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>

#include "graph.h"
#include "users.h"

int min_path(list_graph_t *graph, int src, int dest)
{
	int *distance = calloc(graph->nodes, sizeof(int));
	int *parent = calloc(graph->nodes, sizeof(int));
	int *state = calloc(graph->nodes, sizeof(int));

	for (int i = 0; i < graph->nodes; i++) {
		distance[i] = INF;
		parent[i] = -1;
		state[i] = ALB;
	}

	if (!graph)
		return -1;

	queue_t *q = q_create(sizeof(int), graph->nodes);

	q_enqueue(q, &src);
	state[src] = NEGRU;
	distance[src] = 0;

	while (!q_is_empty(q)) {
		int current_node;
		memcpy(&current_node, q_front(q), sizeof(int));
		q_dequeue(q);

		ll_node_t *neighbor = graph->neighbors[current_node]->head;
		while (neighbor) {
			int neighbour_data = *(int *)neighbor->data;
			if (state[neighbour_data] == ALB) {
				state[neighbour_data] = NEGRU;
				parent[neighbour_data] = current_node;
				distance[neighbour_data] = distance[current_node] + 1;
				q_enqueue(q, &neighbour_data);
			}
			neighbor = neighbor->next;
		}
	}

	if (parent[dest] == -1) {
		free(distance);
		free(parent);
		free(state);
		q_free(q);
		return -1;
	}

	int path_length = distance[dest];

	free(distance);
	free(parent);
	free(state);
	q_free(q);

	return path_length;
}

int compare_ints(void *a, void *b)
{
	return *(int *)a - *(int *)b;
}

static int is_node_in_graph(int n, int nodes)
{
	return n >= 0 && n < nodes;
}

list_graph_t *lg_create(int nodes)
{
	int i;

	list_graph_t *g = malloc(sizeof(*g));
	DIE(!g, "malloc graph failed");

	g->neighbors = malloc(nodes * sizeof(*g->neighbors));
	DIE(!g->neighbors, "malloc neighbours failed");

	for (i = 0; i != nodes; ++i)
		g->neighbors[i] = ll_create(sizeof(int));

	g->nodes = nodes;

	return g;
}

void lg_add_edge(list_graph_t *graph, int src, int dest)
{
	if (!graph || !graph->neighbors || !is_node_in_graph(src, graph->nodes) ||
		!is_node_in_graph(dest, graph->nodes))
		return;

	ll_add_nth_node(graph->neighbors[src], graph->neighbors[src]->size, &dest);
}

ll_node_t *find_node(linked_list_t *ll, int node, unsigned int *pos)
{
	ll_node_t *crt = ll->head;
	unsigned int i;

	for (i = 0; i != ll->size; ++i)
	{
		if (node == *(int *)crt->data)
		{
			*pos = i;
			return crt;
		}

		crt = crt->next;
	}

	return NULL;
}

int lg_has_edge(list_graph_t *graph, int src, int dest)
{
	unsigned int pos;

	if (!graph || !graph->neighbors || !is_node_in_graph(src, graph->nodes) ||
		!is_node_in_graph(dest, graph->nodes))
		return 0;

	if (find_node(graph->neighbors[src], dest, &pos))
		return 1;
	return 0;
}

linked_list_t *lg_get_neighbours(list_graph_t *graph, int node)
{
	if (!graph || !graph->neighbors || !is_node_in_graph(node, graph->nodes))
		return NULL;

	return graph->neighbors[node];
}

void lg_remove_edge(list_graph_t *graph, int src, int dest)
{
	unsigned int pos;

	if (!graph || !graph->neighbors || !is_node_in_graph(src, graph->nodes) ||
		!is_node_in_graph(dest, graph->nodes))
		return;

	if (!find_node(graph->neighbors[src], dest, &pos))
		return;

	ll_node_t *removed_node = ll_remove_nth_node(graph->neighbors[src], pos);
	free(removed_node->data);
	free(removed_node);
}

void lg_free(list_graph_t *graph)
{
	int i;

	for (i = 0; i != graph->nodes; ++i)
		ll_free(graph->neighbors + i);

	free(graph->neighbors);
	free(graph);
}
