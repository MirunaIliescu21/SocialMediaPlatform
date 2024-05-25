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
 * Initialize a new tree structure for the post and store it in the
 * post manager's posts array.
 * Create a new information node containing the post's ID, the user's ID,
 * and the post's title.
 * Insert the newly created information node into the initialized post tree.
 * Increment the post manager's ID counter and the number of posts.
 * Print a confirmation message indicating that the post has been created.
 *
 * @param post_manager The post manager.
 * @param name The name of the user creating the post.
 * @param title The title of the post.
 */
void create_post(tree_post_manager *post_manager, char *name, char *title);

/**
 * @brief Searches for a post with the given ID.
 * Check if there are no posts in the post manager. If there are no posts,
 * return NULL.
 * Loop through each post in the post manager.
 * For each post, compare its ID with the provided post ID.
 * If a matching post ID is found, return the corresponding tree.
 * If no matching post ID is found after checking all posts, return NULL.
 *
 * @param post_manager The post manager containing all posts.
 * @param post_id The ID of the post to search for.
 * @return A pointer to the post tree if found, NULL otherwise.
 */
g_tree_t *search_g_tree(tree_post_manager *post_manager, int post_id);

/**
 * @brief Creates a repost for a given post.
 * Search for the original post using its ID within the post manager's
 * tree structure.
 * Create a new information node for the repost, containing the repost's ID,
 * the user's ID, and NULL for the title.
 * Insert the newly created repost information node into the post tree.
 * If repost_id is provided, insert the repost under the specified parent node.
 * Print a confirmation message indicating that the repost has been created.
 * Increment the post manager's ID counter to ensure uniqueness of repost IDs.
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
 * Base Case: If the current node is NULL, the function returns.
 * Store the node's ID and its level in the respective arrays
 * at the current index.
 * Recursively call the function for each child node, updating the
 * index and level.
 *
 * After processing all children, store the node's ID and level again
 * in the arrays before returning.
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
 * Locate the indices of the given nodes in the Euler tour representation.
 * Determine the range of the search based on the order of the nodes
 * in the Euler tour.
 * Iterate through the range to find the node with the minimum level,
 * which represents the LCA.
 * Return LCA ID: Return the ID of the LCA node.
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
 * @brief Finds the first common repost between two reposts of a post
 * using the lowest common ancestor algorithm.
 * Search for the post with the given ID in the post manager's tree structure.
 * Allocate memory for arrays to store the Euler tour representation and
 * level vectors of the post tree.
 * Create the Euler tour representation and level vectors of the post tree
 * using a recursive function.
 * Find the LCA of the two reposts using their IDs and the Euler tour
 * representation and level vectors.
 * Free the allocated memory for the arrays.
 * Print the ID of the first common repost of the given reposts.
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
 * Search for the specified post ID in the post manager's tree structure.
 * Get the user ID corresponding to the given user name.
 * If the post is a repost, get the title of the original post;
 * otherwise, get its title.
 *  Determine the linked list of likes based on whether the user is liking
 * the original post or a repost.
 * Check if the user has previously liked the post or repost.
 * If not, add the user to the like list and increment the like count.
 * If the user has previously liked the post, remove their like from
 * the like list and decrement the like count.
 * Print a confirmation message indicating whether the user liked or unliked
 * the post or repost.
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
 * Base Case: If the current node is NULL, the function returns.
 * Compare the number of likes of the current node with the maximum likes
 * found so far. If the current node has more likes, update the maximum likes
 * and the corresponding node ID.
 * If the number of likes of the current node equals the maximum likes
 * found so far, compare the IDs of the nodes. If the current node has
 * a smaller ID, update the maximum likes ID.
 * Recursively call the function for each child node
 * to explore the entire tree.
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
 * Search for the specified post ID in the post manager's tree structure.
 * If the post does not exist, the function returns.
 * Initialize variables to store the maximum number of likes and the ID of
 * the post with the maximum likes.
 * Recursively traverse the tree to find the node with the maximum number of
 * likes and update the variables accordingly.
 * Determine ratio result: Compare the ID of the post with the maximum likes
 * to the ID of the original post.
 * Print a message indicating whether the original post has the highest number
 * of likes or if it has been ratio'd by one of its reposts.
 *
 * @param post_manager The post manager.
 * @param post_id The ID of the original post.
 */
void post_ratio(tree_post_manager *post_manager, int post_id);

/**
 * @brief Deletes a post or repost.
 * Search for the specified post ID in the post manager's tree structure.
 * If the post does not exist, the function returns.
 * Delete Post or Repost:
 * If repost_id is 0, indicating the deletion of the original post:
 *		- find the position of the post in the post manager's array of posts.
 *		- print a confirmation message indicating the deletion of the post.
 *		- free the memory associated with the post's tree structure.
 *		- shift the remaining posts in the array to fill the gap left by
 *		the deleted post.
 *		- decrement the count of posts in the post manager.
 * If repost_id is not 0, indicating the deletion of a repost:
 *		- print a confirmation message indicating the deletion of the repost.
 *		- call the delete_subtree function to delete the subtree rooted at the
 *		repost node.
 *
 * @param post_manager The post manager.
 * @param post_id The ID of the original post.
 * @param repost_id The ID of the repost (0 if deleting the original post).
 */
void delete_post(tree_post_manager *post_manager, int post_id, int repost_id);

/**
 * @brief Gets the number of likes for a post or repost.
 * Search for the specified post ID in the post manager's tree structure.
 * If the post does not exist, the function returns.
 * Retrieve Likes:
 * If repost_id is 0, indicating the retrieval of likes for the original post:
 *		- Print a message indicating the number of likes for the original post.
 * If repost_id is not 0, indicating the retrieval of likes for a repost:
 *		- Search for the repost node within the post tree.
 *		- Print a message indicating the number of likes for the repost.
 *
 * @param post_manager The post manager.
 * @param post_id The ID of the original post.
 * @param repost_id The ID of the repost
 * (0 if getting likes for the original post).
 */
void get_likes(tree_post_manager *post_manager, int post_id, int repost_id);

/**
 * @brief Gets the repost tree for a post or repost.
 * Search for the specified post ID in the post manager's tree structure.
 * If the post does not exist, the function returns.
 * Retrieve Reposts:
 * If repost_id is 0, indicating the retrieval of reposts for a post:
 *		- Print the entire subtree of the original post using the
 *		print_generic_tree function.
 * If repost_id is not 0, indicating the retrieval of reposts for a repost:
 *		- Search for the repost node within the post tree.
 *		- Print the subtree rooted at the repost node using the
 *		print_tree_recursive function.
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
