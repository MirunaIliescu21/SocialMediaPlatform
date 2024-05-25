#ifndef POSTS_H
#define POSTS_H

#define MAX_G_TREES 100

#include "generic_tree.h"

/**
 * @brief Manages the collection of posts.
 */
typedef struct {
	g_tree_t **posts;    /* Array of pointers to posts (generic trees) */
	int n_posts;         /* Number of posts */
	int id_counter;      /* Counter for generating unique post IDs */
} tree_post_manager;

/**
 * @brief Creates a new post.
 *
 * @param post_manager The post manager.
 * @param name The name of the user creating the post.
 * @param title The title of the post.
 */
void create_post(tree_post_manager *post_manager, char *name, char *title);

/**
 * @brief Searches for a post with the given ID.
 *
 * @param post_manager The post manager containing all posts.
 * @param post_id The ID of the post to search for.
 * @return A pointer to the post tree if found, NULL otherwise.
 */
g_tree_t *search_g_tree(tree_post_manager *post_manager, int post_id);

/**
 * @brief Creates a repost for a given post.
 *
 * @param post_manager The post manager.
 * @param name The name of the user creating the repost.
 * @param post_id The ID of the original post.
 * @param repost_id The ID of the repost
 * (0 if creating a repost for the original post).
 */
void create_repost(tree_post_manager *post_manager, char *name,
				   int post_id, int repost_id);

/**
 * @brief Creates an Euler tour representation of the repost tree.
 *
 * @param node The current node in the repost tree.
 * @param euler_vector The array to store the Euler tour.
 * @param level_vector The array to store the levels of nodes
 * in the Euler tour.
 * @param index The current index in the Euler tour array.
 * @param level The current level in the tree.
 */
void create_euler_representation(g_node_t *node, int *euler_vector,
								 int *level_vector, int *index, int level);

/**
 * @brief Searches for the lowest common ancestor (LCA) in the Euler tour.
 *
 * @param euler_vector The Euler tour array.
 * @param level_vector The levels array corresponding to the Euler tour.
 * @param repost_id_1 The ID of the first repost.
 * @param repost_id_2 The ID of the second repost.
 * @return The ID of the LCA node.
 */
int search_lca(int *euler_vector, int *level_vector,
			   int repost_id_1, int repost_id_2);

/**
 * @brief Counts the number of nodes in a subtree recursively.
 *
 * @param g_node The root node of the subtree.
 * @return The number of nodes in the subtree.
 */
int count_tree_nodes_recursive(g_node_t *g_node);

/**
 * @brief Counts the number of nodes in a tree.
 *
 * @param g_tree The tree to count the nodes of.
 * @return The number of nodes in the tree.
 */
int count_tree_nodes(g_tree_t *g_tree);

/**
 * @brief Finds the first common repost between two reposts of a post
 * using the lowest common ancestor algorithm.
 *
 * @param post_manager The post manager.
 * @param post_id The ID of the original post.
 * @param repost_id_1 The ID of the first repost.
 * @param repost_id_2 The ID of the second repost.
 */
void common_repost(tree_post_manager *post_manager, int post_id,
				   int repost_id_1, int repost_id_2);

/**
 * @brief Likes or unlikes a post or repost.
 *
 * @param post_manager The post manager.
 * @param name The name of the user liking the post.
 * @param post_id The ID of the original post.
 * @param repost_id The ID of the repost (0 if liking the original post).
 */
void like_post(tree_post_manager *post_manager, char *name,
			   int post_id, int repost_id);

/**
 * @brief Recursively finds the node with the maximum number of likes.
 *
 * @param node The current node in the tree.
 * @param max_likes Pointer to store the maximum number of likes.
 * @param max_likes_id Pointer to store the ID of the node with
 * the maximum likes.
 */
void find_max_likes_recursively(g_node_t *node, int *max_likes,
								int *max_likes_id);

/**
 * @brief Finds the post or repost with the highest number of likes.
 *
 * @param post_manager The post manager.
 * @param post_id The ID of the original post.
 */
void post_ratio(tree_post_manager *post_manager, int post_id);

/**
 * @brief Deletes a post or repost.
 *
 * @param post_manager The post manager.
 * @param post_id The ID of the original post.
 * @param repost_id The ID of the repost (0 if deleting the original post).
 */
void delete_post(tree_post_manager *post_manager, int post_id, int repost_id);

/**
 * @brief Gets the number of likes for a post or repost.
 *
 * @param post_manager The post manager.
 * @param post_id The ID of the original post.
 * @param repost_id The ID of the repost
 * (0 if getting likes for the original post).
 */
void get_likes(tree_post_manager *post_manager, int post_id, int repost_id);

/**
 * @brief Gets the repost tree for a post or repost.
 *
 * @param post_manager The post manager.
 * @param post_id The ID of the original post.
 * @param repost_id The ID of the repost
 * (0 if getting reposts for the original post).
 */
void get_reposts(tree_post_manager *post_manager, int post_id, int repost_id);

/**
 * @brief Handles input commands related to posts and reposts.
 *
 * @param input The input string containing the command and arguments.
 * @param post_manager The post manager.
 */
void handle_input_posts(char *input, tree_post_manager *post_manager);

#endif /* POSTS_H */
