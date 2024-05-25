#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>

#include "linked_list.h"

ll_node_t *get_previous_node(linked_list_t *list, void *data,
							 int (*compare_function)(void *, void *))
{
	if (!list)
		return NULL;

	ll_node_t *prev = list->head;
	ll_node_t *curr = list->head;
	while (curr) {
		if (compare_function(curr->data, data) == 0)
			return prev;
		prev = curr;
		curr = curr->next;
	}
	return NULL;
}

linked_list_t *ll_create(unsigned int data_size)
{
	linked_list_t *ll = calloc(1, sizeof(*ll));
	DIE(!ll, "calloc list");

	ll->data_size = data_size;

	return ll;
}

ll_node_t *get_nth_node(linked_list_t *list, unsigned int n)
{
	unsigned int len = list->size - 1;
	unsigned int i;
	ll_node_t *node = list->head;

	if (len < n)
		n = len;

	for (i = 0; i < n; ++i)
		node = node->next;

	return node;
}

static ll_node_t *create_node(const void *new_data, unsigned int data_size)
{
	ll_node_t *node = calloc(1, sizeof(*node));
	DIE(!node, "calloc node");

	node->data = malloc(data_size);
	DIE(!node->data, "malloc data");

	memcpy(node->data, new_data, data_size);

	return node;
}

void ll_add_nth_node(linked_list_t *list, unsigned int n, const void *new_data)
{
	ll_node_t *new_node, *prev_node;

	if (!list)
		return;

	new_node = create_node(new_data, list->data_size);

	if (!n || !list->size)
	{
		new_node->next = list->head;
		list->head = new_node;
	} else {
		prev_node = get_nth_node(list, n - 1);
		new_node->next = prev_node->next;
		prev_node->next = new_node;
	}

	++list->size;
}

ll_node_t *ll_remove_nth_node(linked_list_t *list, unsigned int n)
{
	ll_node_t *prev_node, *removed_node;

	if (!list || !list->size)
		return NULL;

	if (!n)
	{
		removed_node = list->head;
		list->head = removed_node->next;
		removed_node->next = NULL;
	} else {
		prev_node = get_nth_node(list, n - 1);
		removed_node = prev_node->next;
		prev_node->next = removed_node->next;
		removed_node->next = NULL;
	}

	--list->size;

	return removed_node;
}

unsigned int ll_get_size(linked_list_t *list)
{
	return !list ? 0 : list->size;
}

void ll_free(linked_list_t **pp_list)
{
	ll_node_t *node;

	if (!*pp_list || !pp_list)
		return;

	while ((*pp_list)->size)
	{
		node = ll_remove_nth_node(*pp_list, 0);
		free(node->data);
		free(node);
	}

	free(*pp_list);
	*pp_list = NULL;
}
