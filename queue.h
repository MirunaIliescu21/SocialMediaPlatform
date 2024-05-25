#ifndef QUEUE_H
#define QUEUE_H

#define DIE(condition, message) \
	do { \
		if (condition) { \
			fprintf(stderr, "%s\n", message); \
			exit(EXIT_FAILURE); \
		} \
	} while (0)

typedef struct queue_t queue_t;
/**
 * @struct queue_t
 * @brief Represents a queue.
 */
struct queue_t
{
	unsigned int max_size; /* Maximum number of elements the queue can hold. */
	unsigned int size; /* Current number of elements in the queue. */
	unsigned int data_size; /* Size of the data stored in each element. */
	unsigned int read_idx; /* Index of the next element to be read. */
	unsigned int write_idx; /* Index of the next element to be written. */
	void **buff; /* Buffer to store the elements. */
};

/**
 * Creates a queue.
 *
 * @param data_size - The size of the data in each element.
 * @param max_size - The maximum size of the queue.
 * @return A pointer to the created queue.
 */
queue_t *q_create(unsigned int data_size, unsigned int max_size);

/**
 * Gets the size of the queue.
 *
 * @param q - The queue.
 * @return The size of the queue, or 0 if the queue is NULL.
 */
unsigned int q_get_size(queue_t *q);

/**
 * Checks if the queue is empty.
 *
 * @param q - The queue.
 * @return 1 if the queue is empty, 0 otherwise.
 */
unsigned int q_is_empty(queue_t *q);

/**
 * Gets the front element of the queue.
 *
 * @param q - The queue.
 * @return A pointer to the front element, or NULL if the queue is empty.
 */
void *q_front(queue_t *q);

/**
 * Dequeues an element from the queue.
 *
 * @param q - The queue.
 * @return 1 if the element was dequeued, 0 otherwise.
 */
int q_dequeue(queue_t *q);

/**
 * Enqueues an element to the queue.
 *
 * @param q - The queue.
 * @param new_data - Pointer to the data to be enqueued.
 * @return 1 if the element was enqueued, 0 otherwise.
 */
int q_enqueue(queue_t *q, void *new_data);

/**
 * Clears the queue.
 *
 * @param q - The queue.
 */
void q_clear(queue_t *q);

/**
 * Frees the memory allocated for the queue.
 *
 * @param q - The queue.
 */
void q_free(queue_t *q);

#endif
