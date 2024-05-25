#ifndef FRIENDS_H
#define FRIENDS_H

#define MAX_COMMAND_LEN 500
#define MAX_PEOPLE 550

#include "graph.h"

/**
 * @brief Adds a bidirectional friendship between two users.
 *
 * @param graph The graph representing the network.
 * @param name_1 The name of the first user.
 * @param name_2 The name of the second user.
 */
void add_friend(list_graph_t *graph, char *name_1, char *name_2);

/**
 * @brief Removes the bidirectional friendship between two users.
 *
 * @param graph The graph representing the network.
 * @param name_1 The name of the first user.
 * @param name_2 The name of the second user.
 */
void remove_friend(list_graph_t *graph, char *name_1, char *name_2);

/**
 * @brief Suggests friends for a user based on the friends of their friends.
 *
 * @param graph The graph representing the network.
 * @param name The name of the user to suggest friends for.
 */
void suggestions(list_graph_t *graph, char *name);

/**
 * @brief Calculates and prints the shortest path distance between two users.
 *
 * @param graph The graph representing the network.
 * @param name_1 The name of the first user.
 * @param name_2 The name of the second user.
 */
void get_distance(list_graph_t *graph, char *name_1, char *name_2);

/**
 * @brief Finds and prints the common friends between two users.
 *
 * @param graph The graph representing the network.
 * @param name_1 The name of the first user.
 * @param name_2 The name of the second user.
 */
void common_friends(list_graph_t *graph, char *name_1, char *name_2);

/**
 * @brief Counts and prints the number of friends a user has.
 *
 * @param graph The graph representing the network.
 * @param name The name of the user.
 */
void count_friends(list_graph_t *graph, char *name);

/**
 * @brief Finds and prints the most popular friend of a user.
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
