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
 * Get the user ID corresponding to the given user name.
 * Retrieve the user's friends list from the graph data structure.
 * Create an array to keep track of which users' posts have already been
 * included in the feed. Initialize it to mark the user and their friends.
 * Generate Feed:
 *		Iterate through the posts in the post manager's array in reverse order
 *		(from newest to oldest).
 *		Check if the feed size limit has been reached or if there are no more
 *		posts to process.
 *		For each post, check if the post's author is a friend of the user.
 *		If so, print the post title along with the author's name.
 *		Decrement the feed size counter after printing each eligible post.
 * Free the memory allocated for the frequency array.
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
 * Base Case: If the current node is NULL, the function returns.
 * If the current node represents a repost made by the specified user,
 * print information about the repost.
 * Recursively call the function for each child node to explore the entire
 * repost tree structure.
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
 * Get the unique identifier for the user based on their name.
 * Iterate through the posts in the post manager's array.
 * If the author of a post matches the user ID, print the title of
 * the post as "Posted"
 * Iterate through the posts in the post manager's array again.
 * For each post, recursively traverse the repost tree structure using
 * the print_reposts_recursive function to check if the user has reposted it.
 * If so, print information about the repost.
 *
 * @param post_manager The post manager containing all posts.
 * @param name The name of the user whose profile is to be viewed.
 */
void view_profile(tree_post_manager *post_manager, char *name);

/**
 * @brief Recursively checks which friends have reposted a given post.
 * Base Case: If the current node is NULL, the function returns.
 * Check Level:
 * If the current level is not the root level (level 0), indicating that
 * this is a repost node:
 *		- check if the user who made the repost is a friend of
 *		the original poster.
 *		- if the user is a friend, update the frequency array to mark that
 *		the friend has reposted the content.
 * Recursively call the function for each child node to explore the entire
 * repost tree structure.
 *
 * @param node The current node in the repost tree.
 * @param level The current level in the repost tree.
 * @param frequency Pointer to an array tracking which friends have reposted.
 */
void check_friends_who_reposted(g_node_t *node, int level,
								int **frequency);

/**
 * @brief Displays which friends of a user have reposted a specific post.
 * Search for the specified post ID in the post manager's tree structure.
 * If the post does not exist, the function returns.
 * Obtain the list of friends for the specified user from
 * the graph data structure.
 * Create an array to keep track of which users' friends have reposted
 * the specified post. Initialize it to mark the user's friends.
 * Traverse the repost tree structure of the specified post recursively using
 * the check_friends_who_reposted function to identify friends who have
 * reposted the content. Update the frequency array accordingly.
 * Iterate through the frequency array, and for each user whose friend has
 * reposted the content (marked with a frequency of 2), print their name.
 * Free the memory allocated for the frequency array.
 *
 * @param graph The social graph.
 * @param post_manager The post manager containing all posts.
 * @param name The name of the user.
 * @param post_id The ID of the post to check for reposts.
 */
void friends_repost(list_graph_t *graph, tree_post_manager *post_manager,
					char *name, int post_id);

/**
 * @brief Sorts an array of friends_info structures by the number of
 * connections each friend has.
 * It uses a simple bubble sort algorithm to arrange the friends in
 * descending order of their number of connections.
 *
 * @param friends_vector An array of friends_info structures to be sorted.
 * @param n_friends The number of friends in the array.
 */
void sort_friends_by_connections(friends_info *friends_vector, int n_friends);

/**
 * @brief Sorts an array of friends_info structures by friend IDs.
 * It uses a simple bubble sort algorithm to arrange the friends in
 * ascending order of their IDs.
 *
 * @param friends_vector An array of friends_info structures to be sorted.
 * @param n_friends The number of friends in the array.
 */
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
 * Obtain the unique identifier (user_id) for the given user name.
 * Retrieve the list of friends for the user from the graph.
 *
 * Initialize Data Structures:
 * Create an array frequency to ensure consideration of only the friends of
 * the user.
 * Allocate memory for the 'friends_vector' array to store information
 * about each friend.
 * Initialize variables to track the number of friends (n_friends) and the
 * remaining friends (n_remaining_friends).
 *
 * Populate Friends Vector:
 * Traverse through the user's friend list.
 * Populate the friends_vector array with friend IDs and mark them
 * in the frequency array.
 *
 * Calculate Connections:
 * For each friend in the friends_vector, obtain their friends and
 * count connections common with the user's friends.
 * Update the n_connections field for each friend in the friends_vector.
 *
 * Sort the friends_vector based on the number of connections each friend has.
 *
 * Identify Closest Friend Group:
 * Iterate through the sorted friends_vector array in reverse order.
 * Determine the number of remaining friends needed to form the
 * closest friend group.
 * Adjust the n_remaining_friends count and recalculate connections.
 *
 * Sort the friends_vector array again based on the updated connection counts.
 * (Each time a friend is removed from the friends_vector, all connections
 * that this particular friend had with the remaining friends
 * must also be removed, so it's essential to recalculate the connections
 * and resort the friends vector each time.)
 *
 * Print the names of the users in the closest friend group for the given user.
 * Free the allocated memory for the frequency array and the friends_vector.
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
