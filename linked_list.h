#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define DIE(condition, message) \
	do { \
		if (condition) { \
			fprintf(stderr, "%s\n", message); \
			exit(EXIT_FAILURE); \
		} \
	} while (0)

typedef struct ll_node_t ll_node_t;
typedef struct linked_list_t linked_list_t;

/**
 * @struct ll_node_t
 * @brief Represents a node in a linked list.
 */
struct ll_node_t
{
	void *data; /* Pointer to the data stored in the node. */
	ll_node_t *next; /* Pointer to the next node in the list. */
};

/**
 * @struct linked_list_t
 * @brief Represents a linked list.
 */
struct linked_list_t
{
	ll_node_t *head; /* Pointer to the head node of the list. */
	unsigned int data_size; /* Size of the data stored in each node. */
	unsigned int size; /* Number of nodes in the list. */
};

/**
 * Gets the previous node in the linked list.
 *
 * @param list - The linked list.
 * @param data - The data to find.
 * @param compare_function - Function to compare the data.
 * @return The previous node, or NULL if not found or list is NULL.
 */
ll_node_t *get_previous_node(linked_list_t *list, void *data,
							 int (*compare_function)(void *, void *));

/**
 * Creates a linked list.
 *
 * @param data_size - The size of the data in each node.
 * @return A pointer to the created linked list.
 */
linked_list_t *ll_create(unsigned int data_size);

/**
 * Gets the nth node in the linked list.
 *
 * @param list - The linked list.
 * @param n - The index of the node to get.
 * @return A pointer to the nth node, or the last node if n is out of bounds.
 */
ll_node_t *get_nth_node(linked_list_t *list, unsigned int n);

/**
 * Adds a node at the nth position in the linked list.
 *
 * @param list - The linked list.
 * @param n - The position to add the node.
 * @param new_data - The data to store in the new node.
 */
void ll_add_nth_node(linked_list_t *list, unsigned int n, const void *new_data);

/**
 * Removes the nth node from the linked list.
 *
 * @param list - The linked list.
 * @param n - The position of the node to remove.
 * @return A pointer to the removed node, or NULL if the list is empty.
 */
ll_node_t *ll_remove_nth_node(linked_list_t *list, unsigned int n);

/**
 * Gets the size of the linked list.
 *
 * @param list - The linked list.
 * @return The size of the linked list, or 0 if the list is NULL.
 */
unsigned int ll_get_size(linked_list_t *list);

/**
 * Frees the memory allocated for the linked list.
 *
 * @param pp_list - Pointer to the linked list pointer.
 */
void ll_free(linked_list_t **pp_list);

#endif
