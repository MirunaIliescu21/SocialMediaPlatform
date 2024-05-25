#ifndef FRIENDS_H
#define FRIENDS_H

#define MAX_COMMAND_LEN 500
#define MAX_PEOPLE 550

#include "graph.h"

/**
 * @brief Adds a bidirectional friendship between two users.
 * Get the unique identifiers for both users based on their names.
 * Add an edge in the graph from the first user to the second user
 * and vice versa to ensure mutual friendship.
 * Print a confirmation message indicating that the connection has been added.
 *
 * @param graph The graph representing the network.
 * @param name_1 The name of the first user.
 * @param name_2 The name of the second user.
 */
void add_friend(list_graph_t *graph, char *name_1, char *name_2);

/**
 * @brief Removes the bidirectional friendship between two users.
 * Get the unique identifiers for both users based on their names.
 * Remove the edge in the graph from the first user to the second use
 * and vice versa to ensure the mutual friendship is removed.
 * Print a confirmation message indicating that the connection
 * has been removed.
 *
 * @param graph The graph representing the network.
 * @param name_1 The name of the first user.
 * @param name_2 The name of the second user.
 */
void remove_friend(list_graph_t *graph, char *name_1, char *name_2);

/**
 * @brief Suggests new friends for a user based on the friends of
 * their friends.
 * Get the ID for the user's name
 * Create and initialize an array to keep track of the frequency
 * of potential friend suggestions.
 * Retrieve the list of friends for the user.
 * For each friend, retrieve their friends and mark potential friend
 * suggestions in the frequency array.
 * Exclude the user and their current friends from the suggestions.
 * If there are suggestions, print them;
 * otherwise, indicate that there are no suggestions.
 * @param graph The graph representing the network.
 * @param name The name of the user to suggest friends for.
 */
void suggestions(list_graph_t *graph, char *name);

/**
 * @brief Calculates and prints the shortest path distance between two users.
 * Get the unique identifiers for the two users using their names.
 * Use the 'min_path' function to find the shortest distance between
 * the two user IDs.
 * Print the distance if there is a path between the two users,
 * otherwise indicate that there is no path.
 *
 * @param graph The graph representing the network.
 * @param name_1 The name of the first user.
 * @param name_2 The name of the second user.
 */
void get_distance(list_graph_t *graph, char *name_1, char *name_2);

/**
 * @brief Finds and prints the common friends between two users.
 * Get the unique identifiers for the two users based on their names.
 * Create and initialize an array to keep track of friend relationships.
 * Retrieve the friends lists for both users from the graph.
 * Traverse the friends list of the first user and mark them in
 * the frequency array.
 * Traverse the friends list of the second user and update the frequency
 * array for common friends.
 *  Determine if there are any common friends. (frequency[i] == 2)
 * Print the common friends if any, otherwise indicate that there
 * are no common friends.
 * Free the allocated memory for the frequency array.
 *
 * @param graph The graph representing the network.
 * @param name_1 The name of the first user.
 * @param name_2 The name of the second user.
 */
void common_friends(list_graph_t *graph, char *name_1, char *name_2);

/**
 * @brief Counts and prints the number of friends a user has.
 * Get the unique identifier for the user based on their name.
 * Retrieve the friends list for the user from the graph.
 * Count the number of friends in the list (ll_get_size(friends_list)).
 * Print the user's name along with the number of friends they have.
 *
 * @param graph The graph representing the network.
 * @param name The name of the user.
 */
void count_friends(list_graph_t *graph, char *name);

/**
 * @brief Finds and prints the most popular friend of a user.
 * Get the unique identifier for the user based on their name.
 * Retrieve the list of friends for the user from the graph.
 * Initialize variables to keep track of the friend with the most friends.
 * For each friend, retrieve their friends list and count the number
 * of friends.
 * If a friend has more friends than the current maximum, update the maximum.
 * If the number of friends is the same, choose the friend with the smaller ID.
 * Print the most popular friend, or indicate that the user is the most popular
 * if no friend surpasses their number of friends.
 *
 * @param graph The graph representing the network.
 * @param name The name of the user.
 */
void most_popular_friend(list_graph_t *graph, char *name);

/**
 * @brief Function that handles the calling of every command from task.
 *
 * @param input The input string containing the command and arguments.
 * @param graph The graph representing the network.
 */
void handle_input_friends(char *input, list_graph_t *graph);

#endif /* FRIENDS_H */
