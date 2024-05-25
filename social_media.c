/**
 * The entrypoint of the homework. Every initialization must be done here
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "users.h"
#include "friends.h"
#include "posts.h"
#include "feed.h"

/**
 * Initializez every task based on which task we are running
*/
void init_tasks(void)
{
	#ifdef TASK_1

	#endif

	#ifdef TASK_2

	#endif

	#ifdef TASK_3

	#endif
}

/**
 * Entrypoint of the program, compiled with different defines for each task
 * In the main function, the data structures that we will need are initialized
 * and at the end, the memory is freed after the completion of tasks.
*/
int main(void)
{
	init_users();

	init_tasks();

	list_graph_t *graph = lg_create(MAX_PEOPLE);
	tree_post_manager *post_manager = calloc(1, sizeof(tree_post_manager));
	post_manager->posts = calloc(MAX_G_TREES, sizeof(g_tree_t *));
	DIE(!post_manager->posts, "calloc failed\n");
	post_manager->n_posts = 0;
	post_manager->id_counter = 1;

	char *input = (char *)malloc(MAX_COMMAND_LEN);
	while (1) {
		char *command = fgets(input, MAX_COMMAND_LEN, stdin);

		// If fgets returns null, we reached EOF
		if (!command)
			break;

		#ifdef TASK_1
		handle_input_friends(input, graph);
		#endif

		#ifdef TASK_2
		handle_input_posts(input, post_manager);
		#endif

		#ifdef TASK_3
		handle_input_feed(input, graph, post_manager);
		#endif
	}
	for (int i = 0; i < post_manager->n_posts; i++)
		free_g_tree(post_manager->posts[i]);
	free(post_manager->posts);
	free(post_manager);

	lg_free(graph);

	free_users();
	free(input);

	return 0;
}
