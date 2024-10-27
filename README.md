# Assignment 3

## Description

The purpose of this assignment is to understand and develop a social media platform that combines cloud storage functionality, friend network management, and post sharing. This involves implementing tree data structures and specific algorithms that allow users to add and manage friends, create and interact with posts, and generate a personalized social media feed.

---

## __Explanations:__

### Task 1 - Friendship Network

This task involves implementing the necessary functionalities for managing a friendship network on a social media platform (adding a friend, removing a friend, calculating the minimum graph distance between two friends, generating friend suggestions, displaying mutual friends, showing a user’s friend count, or displaying the friend with the most connections between a given user and their friends).

#### suggestions
* This function identifies friends-of-friends for the specified user who are not already friends with them.
* First, it retrieves the user’s unique ID based on their name. Then, a frequency array is allocated to keep track of potential friend suggestions. The user's friend list is accessed, and for each friend, their list of friends is checked, marking all the user’s friends-of-friends in the frequency array.
* At the end, the user and their current friends are excluded from the suggestions. If there are valid suggestions, they are displayed; otherwise, it indicates that there are no available suggestions for that user.

#### get_distance
* This function calculates and displays the shortest distance between two users in a social network. It uses a breadth-first search algorithm to determine the minimum number of steps needed to reach from one user to the other.
* First, it retrieves the unique identifiers for the two users based on their names. Then, it calls the `min_path` function to calculate the shortest distance between the two users (the `min_path` function was created in SDA lab 7 with slight modifications; comments regarding its functionality are found in the `graph.h` file). If a path exists between the two users, the distance is displayed; otherwise, it indicates that there is no path between them.

#### most_popular_friend
* This function identifies and displays the most popular friend of a user (i.e., the friend with the most friends), based on the friend count of each friend of the specified user.
* First, it retrieves the unique ID of the user based on their name. Then, it accesses the user’s friend list from the graph and initializes max variables (`max_num_friends`, `max_id`) to keep track of the friend with the most connections. The function iterates through each friend of the user, accessing each friend’s list of friends and counting their friend count using the `count_friends` function (for more details on this function, refer to `friends.h`).
* For each iteration, if a friend has more friends than the current maximum (`max_num_friends`), they become the new most popular friend, and if there’s a tie, the friend with the smaller ID is chosen.
* Finally, the function displays the most popular friend. If the user has the highest friend count or has an equal count with another user, it indicates that the user themselves is the most popular (as specified in the assignment prompt).

---

### Task 2 - Posts and Reposts

This task involves implementing the functionalities needed to manage posts and reposts on a social media platform (creating a post, reposting a post or a repost, finding the first common repost for two given reposts, liking a post, deleting a post, displaying the number of likes for a post, etc.).
* For this task, generic tree structures and their functionalities were implemented in `generic_tree.c` and `generic_tree.h` (for more details, see `generic_tree.h`).

#### common_repost
* This function identifies the first common repost between two reposts of the same post.
* First, the function locates the tree of the post corresponding to the `post_id` parameter. Then, it initializes arrays for Eulerian tour representation and level vectors for each tree node (using the Eulerian tour method for lowest common ancestor (LCA) search, as discussed in SDA; see `posts.h` for comments or visit [link](https://www.infoarena.ro/problema/lca) from the course).
* An Eulerian tour representation of the post tree and the level vector is generated using a recursive tree traversal. The LCA search algorithm then determines the ID of the first common repost.
* Finally, after finding the LCA, the function releases memory previously allocated for the Euler and level arrays.

#### like_post
* This function handles liking or unliking posts and reposts.
* It first locates the tree corresponding to the post with `post_id` in the `post_manager` structure. If the post doesn’t exist, the function ends.
* Otherwise, it retrieves the ID of the user liking the post and the title of the post if applicable.
* Based on the presence or absence of the `repost_id` parameter, the function adds or removes the user's like on the post or repost.
* It searches the post’s or repost’s like list for the user ID, removing the like if the user already liked it or adding it if not (using functions specifically created for this purpose).
* The function also updates the total like count (`n_likes`) and displays a corresponding message.

#### ratio
* This function identifies the post or repost with the highest number of likes.
* It first locates the post tree for the given `post_id` in the `post_manager`. If the post doesn’t exist, the function ends.
* Then, it initializes variables to store the maximum number of likes and the ID of the post or repost with the most likes (`max_likes`, `max_likes_id`), initially set to the original post values.
* The tree is traversed recursively to find the node with the most likes, updating the max variables on each iteration. In case of a tie, the post/repost with the smaller ID is chosen (implemented with `find_max_likes_recursively`; see `posts.h`).
* Finally, the function compares the ID of the most liked post with the original post ID, and if the original post also has `max_likes`, it is selected as the most liked post regardless of other IDs found, as specified in the assignment prompt.

---

### Task 3 - Social Media

This task involves implementing functionalities to manage and display posts and interactions in a social network (displaying the most recent posts by a user and their friends, showing all posts and reposts of a user, displaying all friends who reposted a given post, and displaying the largest group of friends in which a user is present).

#### common_groups
* This function identifies and displays the largest clique of friends (including the specified user) formed by modifying the graph of the user and their friends.
* The user_id is obtained for the given username using `get_user_id`, and the user’s friend list is accessed using `lg_get_neighbours`.
* A frequency vector is initialized to ensure that only the user’s friends are considered. Memory is also allocated for a `friends_vector` that stores each friend’s ID and connection count with others (`n_connections`).
* We initialize `n_friends` for the total graph count and update it while iterating through the friend list.
* The user’s friend list is iterated to add IDs to `friends_vector`, marking them in `frequency`.
* The `friends_vector` is then sorted in descending order by connections using `sort_friends_by_connections` (see `feed.h` for details).
* The clique is calculated by iterating through `friends_vector` in descending order; each friend’s connection count is checked to see if they meet the clique condition.
* The `friends_vector` is finally sorted by ID using `sort_friends_by_id` (see `feed.h`) and displays the remaining clique members.

---

## Assignment Comments:

### What did you learn from this assignment?

* How the backend of a social media platform functions.
* Better understanding and implementation of data structures (Graphs, Generic Trees).
* Understanding and implementing an optimal LCA algorithm for trees using Euler representation.

---

## Note:

### Doxygen comments for the implemented structures and functions are included in the ".h" files for readability.
