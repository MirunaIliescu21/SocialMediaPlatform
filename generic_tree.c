#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>

#include "generic_tree.h"

info *create_info(int id, int user_id, char *title)
{
	info *new_info = malloc(sizeof(info));
	new_info->id = id;
	new_info->user_id = user_id;
	if (!title)
		new_info->title = NULL;
	else
		new_info->title = strdup(title);
	new_info->n_likes = 0;
	new_info->likes =  calloc(1, sizeof(linked_list_t));
	DIE(!new_info->likes, "calloc failed\n");
	new_info->likes->head = NULL;
	new_info->likes->size = 0;
	new_info->likes->data_size = sizeof(int);
	return new_info;
}

void free_value_post(void *data)
{
	if (((info *)data)->title)
		free(((info *)data)->title);
	if (((info *)data))
		ll_free(&(((info *)data)->likes));
	free(data);
}

g_tree_t *init_generic_tree(int data_size, void (*free_value_function)(void *),
							int max_size)
{
	g_tree_t *g_tree = calloc(1, sizeof(g_tree_t));
	DIE(!g_tree, "calloc failed");

	g_tree->root = NULL;
	g_tree->data_size = data_size;
	g_tree->size = 0;
	g_tree->free_value = free_value_function;
	g_tree->max_size = max_size;

	return g_tree;
}

g_node_t *search_node_recursive(g_node_t *node, int parent_id) {
	if (!node)
		return NULL;

	if (((info *)node->data)->id == parent_id)
		return node;

	for (int i = 0; i < node->n_children; i++) {
		g_node_t *found_node = search_node_recursive(node->children[i],
													 parent_id);
		if (found_node)
			return found_node;
	}

	return NULL;
}

g_node_t *search_node(g_tree_t *g_tree, int parent_id) {
	if (!g_tree || !g_tree->root)
		return NULL;
	return search_node_recursive(g_tree->root, parent_id);
}

g_node_t *create_node(void *data, int data_size, int max_size)
{
	g_node_t *g_node;

	g_node = calloc(1, sizeof(*g_node));

	DIE(!g_node, "g_node calloc");

	g_node->n_children = 0;
	g_node->children = calloc(max_size, sizeof(g_node_t *));
	DIE(!g_node->children, "calloc failed");

	g_node->data = calloc(1, data_size);
	DIE(!g_node->data, "g_node->data malloc");
	memcpy(g_node->data, data, data_size);

	return g_node;
}

void insert_node(g_tree_t *g_tree, void *data, int parent_id)
{
	g_node_t *new_node = create_node(data, g_tree->data_size, g_tree->max_size);
	g_tree->size++;

	g_node_t *root = g_tree->root;

	if (!root) {
		g_tree->root = new_node;
		return;
	}
	g_node_t *parent_node = search_node(g_tree, parent_id);
	parent_node->children[parent_node->n_children] = new_node;
	parent_node->n_children++;
}

g_node_t *get_the_parent_recursive(g_node_t *node, int node_id,
								   g_node_t *parent)
{
	if (!node)
		return NULL;

	if (((info *)node->data)->id == node_id)
		return parent;

	for (int i = 0; i < node->n_children; i++) {
		g_node_t *found_parent =
		get_the_parent_recursive(node->children[i], node_id, node);
		if (found_parent)
			return found_parent;
	}

	return NULL;
}

g_node_t *get_the_parent(g_tree_t *tree, int node_id)
{
	if (!tree || !tree->root)
		return NULL;

	return get_the_parent_recursive(tree->root, node_id, NULL);
}

void delete_subtree_recursively(g_node_t *node,
								void (*free_value_function)(void *))
{
	if (!node)
		return;

	for (int i = 0; i < node->n_children; ++i)
		delete_subtree_recursively(node->children[i], free_value_function);

	if (node->data)
		free_value_function(node->data);

	free(node->children);
	free(node);
}

void delete_subtree(g_tree_t *g_tree, int parent_id)
{
	if (!g_tree->root)
		return;

	g_node_t *parent_of_parent = get_the_parent(g_tree, parent_id);
	int pos;
	g_node_t *parent_node;
	if (parent_of_parent) {
		pos = -1;
		for (int i = 0; i < parent_of_parent->n_children; i++) {
			if (((info *)parent_of_parent->children[i]->data)->id
				== parent_id) {
				pos = i;
				break;
			}
		}
		parent_node = parent_of_parent->children[pos];
	} else {
		parent_node = g_tree->root;
	}

	delete_subtree_recursively(parent_node, g_tree->free_value);

	if (parent_of_parent) {
		if (pos != -1) {
			for (int i = pos; i < parent_of_parent->n_children - 1; i++) {
				parent_of_parent->children[i] =
				parent_of_parent->children[i + 1];
			}
			parent_of_parent->children[parent_of_parent->n_children - 1] = NULL;
			parent_of_parent->n_children--;
		}

	} else {
		g_tree->root = NULL;
	}
}

void free_g_tree(g_tree_t *g_tree)
{
	if (!g_tree->root) {
		free(g_tree);
		return;
	}

	delete_subtree(g_tree, ((info *)g_tree->root->data)->id);
	free(g_tree);
}

void print_tree_recursive(g_node_t *node, int level)
{
	if (!node)
		return;

	if (level == 0) {
		printf("%s - Post by %s\n", ((info *)node->data)->title,
			   get_user_name(((info *)node->data)->user_id));
	} else {
		printf("Repost #%d by %s\n", ((info *)node->data)->id,
			   get_user_name(((info *)node->data)->user_id));
	}
	for (int i = 0; i < node->n_children; i++)
		print_tree_recursive(node->children[i], level + 1);
}

void print_generic_tree(g_tree_t *g_tree)
{
	if (!g_tree || !g_tree->root) {
		printf("Arborele este gol.\n");
		return;
	}

	print_tree_recursive(g_tree->root, 0);
}
