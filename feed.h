#ifndef FEED_H
#define FEED_H

#include "friends.h"
#include "posts.h"

typedef struct {
	int n_connections;
	int id;
} friends_info;

/**
 * @brief Displays the feed for a user, showing recent posts from friends.
 *
 * @param graph The social graph.
 * @param post_manager The post manager containing all posts.
 * @param name The name of the user whose feed is to be displayed.
 * @param feed_size The number of posts to display in the feed.
 */
void feed(list_graph_t *graph, tree_post_manager *post_manager,
		  char *name, int feed_size);

/**
 * @brief Recursively prints the reposts of a given post by a specific user.
 *
 * @param node The current node in the repost tree.
 * @param level The current level in the repost tree.
 * @param user_id The ID of the user whose reposts are to be printed.
 * @param title The title of the original post.
 */
void print_reposts_recursive(g_node_t *node, int level, int user_id,
							 char *title);

/**
 * @brief Displays the profile of a user, including their posts and reposts.
 *
 * @param post_manager The post manager containing all posts.
 * @param name The name of the user whose profile is to be viewed.
 */
void view_profile(tree_post_manager *post_manager, char *name);

/**
 * @brief Recursively checks which friends have reposted a given post.
 *
 * @param node The current node in the repost tree.
 * @param level The current level in the repost tree.
 * @param frequency Pointer to an array tracking which friends have reposted.
 */
void check_friends_who_reposted(g_node_t *node, int level,
								int **frequency);

/**
 * @brief Displays which friends of a user have reposted a specific post.
 *
 * @param graph The social graph.
 * @param post_manager The post manager containing all posts.
 * @param name The name of the user.
 * @param post_id The ID of the post to check for reposts.
 */
void friends_repost(list_graph_t *graph, tree_post_manager *post_manager,
					char *name, int post_id);

void sort_friends_by_connections(friends_info *friends_vector, int n_friends);
void sort_friends_by_id(friends_info *friends_vector, int n_friends);

/**
 * @brief Displays the common groups of friends for a user.
 * This function calculates and displays the friend group that shares
 * the most mutual connections with the specified user. It considers
 * the social graph to identify mutual friends and determine the closest
 * friend group based on the number of shared connections.
 * The result is printed to the standard output, showing the names of
 * users in the closest friend group.
 *
 * In this function, there are three dynamically allocated arrays:
 *
 * 'frequency': This array is used to keep track of whether a particular
 * user ID is present in the user's friend list.
 *
 * 'friends_vector': This array stores the user IDs of all the friends
 * of the specified user.
 *
 * 'num_friends_vector': This array is used to store the number of mutual
 * friends each friend in the friends_vector array has with the specified user.
 *
 * @param graph The social graph.
 * @param name The name of the user whose common groups are to be displayed.
 */
void common_groups(list_graph_t *graph, char *name);

/**
 * @brief Handles input commands related to the feed and user interactions.
 *
 * @param input The input string containing the command and arguments.
 * @param graph The social graph.
 * @param post_manager The post manager containing all posts.
 */
void handle_input_feed(char *input, list_graph_t *graph,
					   tree_post_manager *post_manager);

#endif /* FEED_H */
