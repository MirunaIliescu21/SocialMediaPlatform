#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "posts.h"

void create_post(tree_post_manager *post_manager, char *name, char *title)
{
	post_manager->posts[post_manager->n_posts] =
	init_generic_tree(sizeof(info), free_value_post, MAX_CHILDREN);
	info *g_node_data  = create_info(post_manager->id_counter,
									 get_user_id(name), title);
	insert_node(post_manager->posts[post_manager->n_posts],
				g_node_data, 0);
	free(g_node_data);
	post_manager->id_counter++;
	post_manager->n_posts++;
	printf("Created %s for %s\n", title, name);
}

g_tree_t *search_g_tree(tree_post_manager *post_manager, int post_id)
{
	if (post_manager->n_posts == 0)
		return NULL;

	for (int i = 0; i < post_manager->n_posts; i++) {
		if (((info *)post_manager->posts[i]->root->data)->id == post_id)
			return post_manager->posts[i];
	}
	return NULL;
}

void create_repost(tree_post_manager *post_manager, char *name,
				   int post_id, int repost_id)
{
	g_tree_t *post_tree = search_g_tree(post_manager, post_id);

	if (!post_tree)
		return;

	info *g_node_data  = create_info(post_manager->id_counter,
									 get_user_id(name), NULL);

	if (repost_id == 0)
		insert_node(post_tree, g_node_data, post_id);
	else
		insert_node(post_tree, g_node_data, repost_id);

	free(g_node_data);

	printf("Created repost #%d for %s\n", post_manager->id_counter, name);

	post_manager->id_counter++;
}

void create_euler_representation(g_node_t *node, int *euler_vector,
								 int *level_vector, int *index, int level)
{
	if (!node)
		return;

	euler_vector[*index] = ((info *)node->data)->id;
	level_vector[*index] = level;
	(*index)++;

	for (int i = 0; i < node->n_children; i++) {
		create_euler_representation(node->children[i], euler_vector,
									level_vector, index, level + 1);
		euler_vector[*index] = ((info *)node->data)->id;
		level_vector[*index] = level;
		(*index)++;
	}
}

int search_lca(int *euler_vector, int *level_vector,
			   int repost_id_1, int repost_id_2)
{
	int index1 = 0;
	int index2 = 0;
	while (euler_vector[index1] != 0) {
		if (euler_vector[index1] == repost_id_1)
			break;
		index1++;
	}
	while (euler_vector[index2] != 0) {
		if (euler_vector[index2] == repost_id_2)
			break;
		index2++;
	}
	if (index1 > index2) {
		int aux = index1;
		index1 = index2;
		index2 = aux;
	}
	int lca_id = euler_vector[index1];
	int min_level = level_vector[index1];
	for (int i = index1 + 1; i <= index2; i++) {
		if (level_vector[i] < min_level) {
			lca_id = euler_vector[i];
			min_level = level_vector[i];
		}
	}
	return lca_id;
}

int count_tree_nodes_recursive(g_node_t *g_node) {
	if (!g_node)
		return 0;

	int count = 1;

	for (int i = 0; i < g_node->n_children; i++)
		count += count_tree_nodes_recursive(g_node->children[i]);

	return count;
}

int count_tree_nodes(g_tree_t *g_tree) {
	if (!g_tree)
		return 0;

	return count_tree_nodes_recursive(g_tree->root);
}

void common_repost(tree_post_manager *post_manager, int post_id,
				   int repost_id_1, int repost_id_2)
{
	g_tree_t *post_tree = search_g_tree(post_manager, post_id);

	if (!post_tree)
		return;

	int vector_length = 2 * count_tree_nodes(post_tree);
	int *euler_vector = calloc(vector_length, sizeof(int));
	DIE(!euler_vector, "calloc failed\n");
	int *level_vector = calloc(vector_length, sizeof(int));
	DIE(!level_vector, "calloc failed\n");
	int level = 0;
	int index = 0;
	create_euler_representation(post_tree->root, euler_vector, level_vector,
								&index, level);
	int lca_id = search_lca(euler_vector, level_vector, repost_id_1,
							repost_id_2);
	free(euler_vector);
	free(level_vector);
	printf("The first common repost of %d and %d is %d\n",
		   repost_id_1, repost_id_2, lca_id);
}

void like_post(tree_post_manager *post_manager, char *name,
			   int post_id, int repost_id)
{
	g_tree_t *post_tree = search_g_tree(post_manager, post_id);

	if (!post_tree)
		return;

	int user_id = get_user_id(name);
	char *title = ((info *)post_tree->root->data)->title;

	linked_list_t *g_node_list;
	g_node_t *g_node;
	if (repost_id == 0) {
		g_node_list = ((info *)post_tree->root->data)->likes;
	} else {
		g_node = search_node(post_tree, repost_id);
		g_node_list = ((info *)g_node->data)->likes;
	}
	ll_node_t *prev_node = get_previous_node(g_node_list,
											 &user_id, compare_ints);
	if (!prev_node) {
		ll_add_nth_node(g_node_list, g_node_list->size, &user_id);
		if (repost_id == 0) {
			((info *)post_tree->root->data)->n_likes++;
			printf("User %s liked post %s\n", name, title);
		} else {
			((info *)g_node->data)->n_likes++;
			printf("User %s liked repost %s\n", name, title);
		}
	} else {
		ll_node_t *removed_node;
		if (*((int *)g_node_list->head->data) == user_id) {
			removed_node = ll_remove_nth_node(g_node_list, 0);
			free(removed_node->data);
			free(removed_node);
		} else {
			removed_node = prev_node->next;
			prev_node->next = prev_node->next->next;
			free(removed_node->data);
			free(removed_node);
			g_node_list->size--;
		}
		if (repost_id == 0) {
			((info *)post_tree->root->data)->n_likes--;
			printf("User %s unliked post %s\n", name, title);
		} else {
			((info *)g_node->data)->n_likes--;
			printf("User %s unliked repost %s\n", name, title);
		}
	}
}

void find_max_likes_recursively(g_node_t *node, int *max_likes,
								int *max_likes_id)
{
	if (!node)
		return;

	if (((info *)node->data)->n_likes > *max_likes) {
		*max_likes = ((info *)node->data)->n_likes;
		*max_likes_id = ((info *)node->data)->id;
	} else {
		if (((info *)node->data)->n_likes == *max_likes) {
			if (((info *)node->data)->id < *max_likes_id)
				*max_likes_id = ((info *)node->data)->id;
		}
	}

	for (int i = 0; i < node->n_children; i++)
		find_max_likes_recursively(node->children[i], max_likes, max_likes_id);
}

void post_ratio(tree_post_manager *post_manager, int post_id)
{
	g_tree_t *post_tree = search_g_tree(post_manager, post_id);

	if (!post_tree)
		return;

	int max_likes = ((info *)post_tree->root->data)->n_likes;
	int max_likes_id = ((info *)post_tree->root->data)->id;

	g_node_t *root = post_tree->root;

	find_max_likes_recursively(root, &max_likes, &max_likes_id);

	if (max_likes_id == ((info *)post_tree->root->data)->id)
		printf("The original post is the highest rated\n");
	else
		printf("Post %d got ratio'd by repost %d\n", post_id, max_likes_id);
}

void delete_post(tree_post_manager *post_manager, int post_id, int repost_id)
{
	g_tree_t *post_tree = search_g_tree(post_manager, post_id);

	if (!post_tree)
		return;

	if (repost_id == 0) {
		int pos = -1;
		for (int i = 0; i < post_manager->n_posts; i++) {
			if (((info *)post_manager->posts[i]->root->data)->id == post_id) {
				pos = i;
				break;
			}
		}
		printf("Deleted %s\n", ((info *)post_tree->root->data)->title);
		free_g_tree(post_tree);
		for (int i = pos; i < post_manager->n_posts - 1; i++)
			post_manager->posts[i] = post_manager->posts[i + 1];

		post_manager->posts[post_manager->n_posts - 1] = NULL;
		post_manager->n_posts--;
	} else {
		printf("Deleted repost #%d of post %s\n", repost_id,
			   ((info *)post_tree->root->data)->title);
		delete_subtree(post_tree, repost_id);
	}
}

void get_likes(tree_post_manager *post_manager, int post_id, int repost_id)
{
	g_tree_t *post_tree = search_g_tree(post_manager, post_id);

	if (!post_tree)
		return;

	if (repost_id == 0) {
		printf("Post %s has %d likes\n",
			   ((info *)post_tree->root->data)->title,
			   ((info *)post_tree->root->data)->n_likes);
	} else {
		g_node_t *g_node = search_node(post_tree, repost_id);
		printf("Repost #%d has %d likes\n", repost_id,
			   ((info *)g_node->data)->n_likes);
	}
}

void get_reposts(tree_post_manager *post_manager, int post_id, int repost_id)
{
	g_tree_t *post_tree = search_g_tree(post_manager, post_id);

	if (!post_tree)
		return;

	if (repost_id == 0) {
		print_generic_tree(post_tree);
	} else {
		g_node_t *parent = search_node(post_tree, repost_id);
		print_tree_recursive(parent, 1);
	}
}

void handle_input_posts(char *input, tree_post_manager *post_manager)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");
	if (!cmd)
		return;
	if (!strcmp(cmd, "create")) {
		char *name = strtok(NULL, "\n ");
		char *title = strtok(NULL, "\n");
		create_post(post_manager, name, title);
	} else if (!strcmp(cmd, "repost")) {
		char *name = strtok(NULL, "\n ");
		char *token = strtok(NULL, "\n ");
		int post_id = atoi(token);
		token = strtok(NULL, "\n ");
		int repost_id;
		if (token)
			repost_id = atoi(token);
		else
			repost_id = 0;
		create_repost(post_manager, name, post_id, repost_id);
	} else if (!strcmp(cmd, "common-repost")) {
		char *token = strtok(NULL, "\n ");
		int post_id = atoi(token);
		token = strtok(NULL, "\n ");
		int repost_id_1 = atoi(token);
		token = strtok(NULL, "\n ");
		int repost_id_2 = atoi(token);
		common_repost(post_manager, post_id, repost_id_1, repost_id_2);
	} else if (!strcmp(cmd, "like")) {
		char *name = strtok(NULL, "\n ");
		char *token = strtok(NULL, "\n ");
		int post_id = atoi(token);
		token = strtok(NULL, "\n ");
		int repost_id;
		if (token)
			repost_id = atoi(token);
		else
			repost_id = 0;
		like_post(post_manager, name, post_id, repost_id);
	} else if (!strcmp(cmd, "ratio")) {
		char *token = strtok(NULL, "\n ");
		int post_id = atoi(token);
		post_ratio(post_manager, post_id);
	} else if (!strcmp(cmd, "delete")) {
		char *token = strtok(NULL, "\n ");
		int post_id = atoi(token);
		token = strtok(NULL, "\n ");
		int repost_id;
		if (token)
			repost_id = atoi(token);
		else
			repost_id = 0;
		delete_post(post_manager, post_id, repost_id);
	} else if (!strcmp(cmd, "get-likes")) {
		char *token = strtok(NULL, "\n ");
		int post_id = atoi(token);
		token = strtok(NULL, "\n ");
		int repost_id;
		if (token)
			repost_id = atoi(token);
		else
			repost_id = 0;
		get_likes(post_manager, post_id, repost_id);
	} else if (!strcmp(cmd, "get-reposts")) {
		char *token = strtok(NULL, "\n ");
		int post_id = atoi(token);
		token = strtok(NULL, "\n ");
		int repost_id;
		if (token)
			repost_id = atoi(token);
		else
			repost_id = 0;
		get_reposts(post_manager, post_id, repost_id);
	}
	free(commands);
}
