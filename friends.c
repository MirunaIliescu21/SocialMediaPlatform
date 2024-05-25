#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friends.h"
#include "users.h"

void add_friend(list_graph_t *graph, char *name_1, char *name_2)
{
	int id_1 = (int)get_user_id(name_1);
	int id_2 = (int)get_user_id(name_2);

	lg_add_edge(graph, id_1, id_2);
	lg_add_edge(graph, id_2, id_1);

	printf("Added connection %s - %s\n", name_1, name_2);
}

void remove_friend(list_graph_t *graph, char *name_1, char *name_2)
{
	int id_1 = get_user_id(name_1);
	int id_2 = get_user_id(name_2);

	lg_remove_edge(graph, id_1, id_2);
	lg_remove_edge(graph, id_2, id_1);

	printf("Removed connection %s - %s\n", name_1, name_2);
}

void suggestions(list_graph_t *graph, char *name)
{
	int id = get_user_id(name);

	int *frequency = calloc(MAX_PEOPLE, sizeof(int));
	DIE(!frequency, "calloc failed\n");

	linked_list_t *friends_list = lg_get_neighbours(graph, id);

	ll_node_t *current_friend = friends_list->head;

	while (current_friend) {
		linked_list_t *friends_of_friends_list =
		lg_get_neighbours(graph, *(int *)current_friend->data);
		ll_node_t *current_friend_of_friend = friends_of_friends_list->head;
		while (current_friend_of_friend) {
			frequency[*(int *)current_friend_of_friend->data] = 1;
			current_friend_of_friend = current_friend_of_friend->next;
		}
		current_friend = current_friend->next;
	}

	current_friend = friends_list->head;

	while (current_friend) {
		frequency[*(int *)current_friend->data] = 0;
		current_friend = current_friend->next;
	}
	frequency[id] = 0;

	int have_suggestions = 0;

	for (int i = 0; i < MAX_PEOPLE; i++) {
		if (frequency[i] == 1) {
			have_suggestions = 1;
			break;
		}
	}

	if (have_suggestions == 0) {
		printf("There are no suggestions for %s\n", name);
		free(frequency);
		return;
	}
	printf("Suggestions for %s:\n", name);

	for (int i = 0; i < MAX_PEOPLE; i++) {
		if (frequency[i] == 1)
			printf("%s\n", get_user_name(i));
	}
	free(frequency);
}

void get_distance(list_graph_t *graph, char *name_1, char *name_2)
{
	int id_1 = get_user_id(name_1);
	int id_2 = get_user_id(name_2);

	int distance = min_path(graph, id_1, id_2);
	if (distance == -1)
		printf("There is no way to get from %s to %s\n", name_1, name_2);
	else
		printf("The distance between %s - %s is %d\n",
			   name_1, name_2, distance);
}

void common_friends(list_graph_t *graph, char *name_1, char *name_2)
{
	int id_1 = get_user_id(name_1);
	int id_2 = get_user_id(name_2);

	int *frequency = calloc(MAX_PEOPLE, sizeof(int));
	DIE(!frequency, "calloc failed\n");

	linked_list_t *friends_list_1 = lg_get_neighbours(graph, id_1);
	linked_list_t *friends_list_2 = lg_get_neighbours(graph, id_2);

	ll_node_t *current_friend_1 = friends_list_1->head;
	while (current_friend_1) {
		frequency[*(int *)current_friend_1->data] = 1;
		current_friend_1 = current_friend_1->next;
	}

	ll_node_t *current_friend_2 = friends_list_2->head;
	while (current_friend_2) {
		if (frequency[*(int *)current_friend_2->data] == 1)
			frequency[*(int *)current_friend_2->data] = 2;
		current_friend_2 = current_friend_2->next;
	}

	int have_common_friends = 0;

	for (int i = 0; i < MAX_PEOPLE; i++) {
		if (frequency[i] == 2) {
			have_common_friends = 1;
			break;
		}
	}

	if (have_common_friends == 0) {
		printf("No common friends for %s and %s\n", name_1, name_2);
		free(frequency);
		return;
	}
	printf("The common friends between %s and %s are:\n", name_1, name_2);

	for (int i = 0; i < MAX_PEOPLE; i++) {
		if (frequency[i] == 2)
			printf("%s\n", get_user_name(i));
	}
	free(frequency);
}

void count_friends(list_graph_t *graph, char *name)
{
	int id = get_user_id(name);

	linked_list_t *friends_list = lg_get_neighbours(graph, id);
	int num_friends =  ll_get_size(friends_list);
	printf("%s has %d friends\n", name, num_friends);
}

void most_popular_friend(list_graph_t *graph, char *name)
{
	int id = get_user_id(name);

	linked_list_t *friends_list = lg_get_neighbours(graph, id);
	int num_friends =  ll_get_size(friends_list);
	int max_num_friends = num_friends;
	int max_id = id;

	ll_node_t *current_friend = friends_list->head;
	while (current_friend) {
		linked_list_t *friends_of_friends_list =
		lg_get_neighbours(graph, *(int *)current_friend->data);
		int num_friends_of_friends =  ll_get_size(friends_of_friends_list);
		if (num_friends_of_friends > max_num_friends) {
			max_num_friends = num_friends_of_friends;
			max_id = *(int *)current_friend->data;
		} else {
			if (num_friends_of_friends == max_num_friends) {
				if (*(int *)current_friend->data < max_id) {
					max_num_friends = num_friends_of_friends;
					max_id = *(int *)current_friend->data;
				}
			}
		}
		current_friend = current_friend->next;
	}
	if (num_friends == max_num_friends)
		printf("%s is the most popular\n", name);
	else
		printf("%s is the most popular friend of %s\n",
			   get_user_name(max_id), name);
}

void handle_input_friends(char *input, list_graph_t *graph)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "add")) {
		char *name_1 = strtok(NULL, "\n ");
		char *name_2 = strtok(NULL, "\n ");
		add_friend(graph, name_1, name_2);
	} else if (!strcmp(cmd, "remove")) {
		char *name_1 = strtok(NULL, "\n ");
		char *name_2 = strtok(NULL, "\n ");
		remove_friend(graph, name_1, name_2);
	} else if (!strcmp(cmd, "suggestions")) {
		char *name = strtok(NULL, "\n ");
		suggestions(graph, name);
	} else if (!strcmp(cmd, "distance")) {
		char *name_1 = strtok(NULL, "\n ");
		char *name_2 = strtok(NULL, "\n ");
		get_distance(graph, name_1, name_2);
	} else if (!strcmp(cmd, "common")) {
		char *name_1 = strtok(NULL, "\n ");
		char *name_2 = strtok(NULL, "\n ");
		common_friends(graph, name_1, name_2);
	} else if (!strcmp(cmd, "friends")) {
		char *name = strtok(NULL, "\n ");
		count_friends(graph, name);
	} else if (!strcmp(cmd, "popular")) {
		char *name = strtok(NULL, "\n ");
		most_popular_friend(graph, name);
	}

	free(commands);
}
