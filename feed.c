#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "feed.h"
#include "users.h"

void feed(list_graph_t *graph, tree_post_manager *post_manager,
		  char *name, int feed_size)
{
	int user_id = get_user_id(name);
	linked_list_t *friends_list = lg_get_neighbours(graph, user_id);

	int *frequency = calloc(MAX_PEOPLE, sizeof(int));
	DIE(!frequency, "calloc failed\n");

	ll_node_t *current_friend = friends_list->head;
	while (current_friend) {
		frequency[*(int *)current_friend->data] = 1;
		current_friend = current_friend->next;
	}
	frequency[user_id] = 1;

	for (int i = post_manager->n_posts - 1; i >= 0; i--) {
		if (feed_size == 0)
			break;
		g_node_t *root = post_manager->posts[i]->root;
		int root_user_id = ((info *)root->data)->user_id;
		if (frequency[root_user_id] == 1) {
			printf("%s: %s\n", get_user_name(root_user_id),
				   ((info *)root->data)->title);
			feed_size--;
		}
	}
	free(frequency);
}

void print_reposts_recursive(g_node_t *node, int level, int user_id,
							 char *title)
{
	if (!node)
		return;

	if (level != 0) {
		if (((info *)node->data)->user_id == user_id)
			printf("Reposted: %s\n", title);
	}

	for (int i = 0; i < node->n_children; i++)
		print_reposts_recursive(node->children[i], level + 1, user_id, title);
}

void view_profile(tree_post_manager *post_manager, char *name)
{
	int user_id = get_user_id(name);

	for (int i = 0; i < post_manager->n_posts; i++) {
		g_node_t *root = post_manager->posts[i]->root;
		int root_user_id = ((info *)root->data)->user_id;
		if (root_user_id == user_id)
			printf("Posted: %s\n",  ((info *)root->data)->title);
	}
	for (int i = 0; i < post_manager->n_posts; i++) {
		g_node_t *root = post_manager->posts[i]->root;
		print_reposts_recursive(root, 0, user_id, ((info *)root->data)->title);
	}
}

void check_friends_who_reposted(g_node_t *node, int level,
								int **frequency)
{
	if (!node)
		return;

	if (level != 0) {
		if ((*frequency)[((info *)node->data)->user_id] == 1)
			(*frequency)[((info *)node->data)->user_id] = 2;
	}

	for (int i = 0; i < node->n_children; i++)
		check_friends_who_reposted(node->children[i], level + 1, frequency);
}

void friends_repost(list_graph_t *graph, tree_post_manager *post_manager,
					char *name, int post_id)
{
	g_tree_t *post_tree = search_g_tree(post_manager, post_id);

	if (!post_tree)
		return;

	int user_id = get_user_id(name);
	linked_list_t *friends_list = lg_get_neighbours(graph, user_id);

	int *frequency = calloc(MAX_PEOPLE, sizeof(int));
	DIE(!frequency, "calloc failed\n");

	ll_node_t *current_friend = friends_list->head;
	while (current_friend) {
		frequency[*(int *)current_friend->data] = 1;
		current_friend = current_friend->next;
	}

	check_friends_who_reposted(post_tree->root, 0, &frequency);

	for (int i = 0; i < MAX_PEOPLE; i++) {
		if (frequency[i] == 2)
			printf("%s\n", get_user_name(i));
	}
	free(frequency);
}

void sort_friends_by_connections(friends_info *friends_vector, int n_friends)
{
	for (int i = 0; i < n_friends; i++) {
		for (int j = i + 1; j < n_friends; j++) {
			if (friends_vector[i].n_connections <
				friends_vector[j].n_connections) {
				int aux = friends_vector[i].id;
				friends_vector[i].id = friends_vector[j].id;
				friends_vector[j].id = aux;

				aux = friends_vector[i].n_connections;
				friends_vector[i].n_connections =
				friends_vector[j].n_connections;
				friends_vector[j].n_connections = aux;
			}
		}
	}
}

void sort_friends_by_id(friends_info *friends_vector, int n_friends)
{
	for (int i = 0; i < n_friends; i++) {
		for (int j = i + 1; j < n_friends; j++) {
			if (friends_vector[i].id > friends_vector[j].id) {
				int aux = friends_vector[i].id;
				friends_vector[i].id = friends_vector[j].id;
				friends_vector[j].id = aux;

				aux = friends_vector[i].n_connections;
				friends_vector[i].n_connections =
				friends_vector[j].n_connections;
				friends_vector[j].n_connections = aux;
			}
		}
	}
}

void common_groups(list_graph_t *graph, char *name)
{
	int user_id = get_user_id(name);
	linked_list_t *friends_list = lg_get_neighbours(graph, user_id);

	// asta e un vector cu care ne asiguram ca luam in calcul
	// doar elementele din clica(adica doar prietenii lui user_id)
	int *frequency = calloc(MAX_PEOPLE, sizeof(int));
	DIE(!frequency, "calloc failed\n");
	// asta e un vector cu toti prietenii lui user_id
	friends_info *friends_vector =
	calloc(ll_get_size(friends_list), sizeof(friends_info));
	DIE(!friends_vector, "calloc failed\n");

	int n_friends = 0;
	ll_node_t *current_friend = friends_list->head;

	while (current_friend) {
		friends_vector[n_friends].id = *(int *)current_friend->data;
		n_friends++;
		frequency[*(int *)current_friend->data] = 1;
		current_friend = current_friend->next;
	}

	for (int i = 0; i < n_friends; i++) {
		linked_list_t *friends__of_friends_list =
		lg_get_neighbours(graph, friends_vector[i].id);
		ll_node_t *current_friend_of_friend = friends__of_friends_list->head;
		while (current_friend_of_friend) {
			if (frequency[*(int *)current_friend_of_friend->data] == 1)
				friends_vector[i].n_connections++;
			current_friend_of_friend = current_friend_of_friend->next;
		}
	}

	sort_friends_by_connections(friends_vector, n_friends);

	int n_remaining_friends = n_friends;

	for (int i = n_friends - 1; i >= 0; i--) {
		if (friends_vector[i].n_connections >= n_remaining_friends - 1) {
			n_remaining_friends = i + 1;
			break;
		}
		// recalculam nr de conexiuni si resortam vectorul
		linked_list_t *friends__of_friends_list =
		lg_get_neighbours(graph, friends_vector[i].id);
		ll_node_t *current_friend_of_friend = friends__of_friends_list->head;
		while (current_friend_of_friend) {
			for (int j = 0; j < i; j++) {
				if (friends_vector[j].id ==
					*(int *)current_friend_of_friend->data)
					friends_vector[j].n_connections--;
			}
			current_friend_of_friend = current_friend_of_friend->next;
		}
		n_remaining_friends--;
		sort_friends_by_connections(friends_vector, n_remaining_friends);
	}

	friends_vector[n_remaining_friends].id = user_id;
	friends_vector[n_remaining_friends].n_connections = n_friends;
	n_remaining_friends++;

	sort_friends_by_id(friends_vector, n_remaining_friends);

	printf("The closest friend group of %s is:\n", name);
	for (int i = 0; i < n_remaining_friends; i++)
		printf("%s\n", get_user_name(friends_vector[i].id));
	free(frequency);
	free(friends_vector);
}

void handle_input_feed(char *input, list_graph_t *graph,
					   tree_post_manager *post_manager)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "feed")) {
		char *name = strtok(NULL, "\n ");
		char *token = strtok(NULL, "\n ");
		int feed_size = atoi(token);
		feed(graph, post_manager, name, feed_size);
	} else if (!strcmp(cmd, "view-profile")) {
		char *name = strtok(NULL, "\n ");
		view_profile(post_manager, name);
	} else if (!strcmp(cmd, "friends-repost")) {
		char *name = strtok(NULL, "\n ");
		char *token = strtok(NULL, "\n ");
		int post_id = atoi(token);
		friends_repost(graph, post_manager, name, post_id);
	} else if (!strcmp(cmd, "common-group")) {
		char *name = strtok(NULL, "\n ");
		common_groups(graph, name);
	}

	free(commands);
}
