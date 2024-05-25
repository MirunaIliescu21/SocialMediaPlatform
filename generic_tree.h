#ifndef GENERIC_TREE_H
#define GENERIC_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "users.h"
#include "graph.h"

#define MAX_CHILDREN 100

/**
 * @brief Structure representing a node in the generic tree.
 */
typedef struct g_node_t g_node_t;
struct g_node_t
{
	void *data; /* Pointer to the data stored in the node. */
	g_node_t **children; /* Array of pointers to child nodes. */
	int n_children; /* Number of children nodes. */
};

/**
 * @brief Structure representing the generic tree.
 */
typedef struct g_tree_t g_tree_t;
struct g_tree_t
{
	g_node_t *root; /* Pointer to the root node of the tree. */
	int data_size; /* Size of the data stored in each node. */
	int size; /* Total number of nodes in the tree. */
	void (*free_value)(void *value); /* Function pointer to free
	the data in each node. */
	int max_size; /* Maximum number of children nodes. */
};

/**
 * @brief Structure representing information stored in the tree nodes.
 */
typedef struct {
	int id; /* ID of the info. */
	int user_id; /* User ID associated with the info. */
	char *title; /* Title of the info. */
	linked_list_t *likes; /*Linked list of likes. */
	int n_likes; /* Number of likes. */
} info;

/**
 * @brief Creates an info structure with the given id, user_id, and title.
 *
 * @param id The ID of the info.
 * @param user_id The user ID associated with the info.
 * @param title The title of the info. Can be NULL.
 * @return A pointer to the created info structure.
 */
info *create_info(int id, int user_id, char *title);

/**
 * @brief Frees the memory allocated for an info structure.
 *
 * @param data A pointer to the info structure to be freed.
 */
void free_value_post(void *data);

/**
 * @brief Initializes a generic tree.
 *
 * @param data_size The size of the data to be stored in each node.
 * @param free_value_function Function to free the data in each node.
 * @param max_size The maximum number of children for each node.
 * @return A pointer to the created generic tree.
 */
g_tree_t *init_generic_tree(int data_size,
							void (*free_value_function)(void *), int max_size);

/**
 * @brief Recursively searches for a node with the given parent_id.
 *
 * @param node The node to start the search from.
 * @param parent_id The ID of the parent to search for.
 * @return A pointer to the found node, or NULL if not found.
 */
g_node_t *search_node_recursive(g_node_t *node, int parent_id);

/**
 * @brief Searches for a node with the given parent_id in the generic tree.
 *
 * @param tree The generic tree to search in.
 * @param parent_id The ID of the parent to search for.
 * @return A pointer to the found node, or NULL if not found.
 */
g_node_t *search_node(g_tree_t *tree, int parent_id);

/**
 * @brief Creates a new node with the given data.
 *
 * @param data The data to be stored in the node.
 * @param data_size The size of the data.
 * @param max_size The maximum number of children for the node.
 * @return A pointer to the created node.
 */
g_node_t *create_node(void *data, int data_size, int max_size);

/**
 * @brief Inserts a new node with the given data into the generic tree.
 *
 * @param g_tree The generic tree to insert the node into.
 * @param data The data to be stored in the new node.
 * @param node The ID of the parent node to insert under.
 * @param max_size The maximum number of children for the new node.
 */
void insert_node(g_tree_t *g_tree, void *data, int node);

/**
 * @brief Recursively searches for the parent of a node with the given node_id.
 *
 * @param node The node to start the search from.
 * @param node_id The ID of the node to find the parent of.
 * @param parent The parent node.
 * @return A pointer to the parent node, or NULL if not found.
 */
g_node_t *get_the_parent_recursive(g_node_t *node, int node_id,
								   g_node_t *parent);

/**
 * @brief Gets the parent of a node with the given node_id in the generic tree.
 *
 * @param tree The generic tree to search in.
 * @param node_id The ID of the node to find the parent of.
 * @return A pointer to the parent node, or NULL if not found.
 */
g_node_t *get_the_parent(g_tree_t *tree, int node_id);

/**
 * @brief Counts the number of nodes in a subtree recursively.
 * Base Case: If the current node is NULL, the function returns 0,
 * indicating that there are no nodes.
 * For each node, increment the count by 1, representing the current node.
 * Recursively call the function for each child node and add their counts
 * to the total count.
 * After processing all children, return the total count, which represents
 * the number of nodes in the tree.
 *
 * @param g_node The root node of the subtree.
 * @return The number of nodes in the subtree.
 */
int count_tree_nodes_recursive(g_node_t *g_node);

/**
 * @brief Counts the number of nodes in a tree.
 * Base Case: If the input tree pointer g_tree is NULL, the function returns 0,
 * indicating that there are no nodes in the tree.
 * If the input tree is not NULL, the function calls the
 * count_tree_nodes_recursive function with the root node of the tree as the
 * starting point for counting nodes.
 *
 * @param g_tree The tree to count the nodes of.
 * @return The number of nodes in the tree.
 */
int count_tree_nodes(g_tree_t *g_tree);

/**
 * @brief Recursively deletes a subtree starting from the given node.
 *
 * @param node The node to start deleting from.
 * @param free_value_function Function to free the data in each node.
 */
void delete_subtree_recursively(g_node_t *node,
								void (*free_value_function)(void *));

/**
 * @brief Deletes a subtree starting from the node with the given parent_id.
 *
 * @param g_tree The generic tree to delete from.
 * @param parent_id The ID of the parent node to start deleting from.
 */
void delete_subtree(g_tree_t *g_tree, int parent_id);

/**
 * @brief Frees the memory allocated for the generic tree.
 *
 * @param g_tree The generic tree to be freed.
 */
void free_g_tree(g_tree_t *g_tree);

/**
 * @brief Recursively prints the tree starting from the given node.
 *
 * @param node The node to start printing from.
 * @param level The current level in the tree.
 */
void print_tree_recursive(g_node_t *node, int level);

/**
 * @brief Prints the generic tree.
 *
 * @param g_tree The generic tree to be printed.
 */
void print_generic_tree(g_tree_t *g_tree);

#endif /* GENERIC_TREE_H */
