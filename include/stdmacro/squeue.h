
#if !defined(STDMACRO_SQUEUE_H)
#define STDMACRO_SQUEUE_H

#include <stdbool.h>
#include <stdmacro/array_size.h>

/**
 * struct_squeue - declares unnamed static queue structure.
 * @basetype:   the type of data in queue.
 * @queue_size: the array size of queue.
 * 
 * struct - metadata for static queue.
 * @head: index of first element in queue.
 * @tail: index of last element in queue.
 * @data: the array that stores elements of queue.
 * 
 * Example:
 *		// Declare static queue structure, struct squeue_int, with queue size 10
 *		STRUCT_SQUEUE(int, 10);
 *		struct squeue_int int_q;
 *		// Declare static queue structure, struct squeue_double, and name it double_q 
 *		STRUCT_SQUEUE(double, 100) double_q;
 * 
 * WARNING: must call SQUEUE_INIT before using squeue API.
 */

#define STRUCT_SQUEUE(basetype, queue_size) \
struct squeue_ ## basetype { \
	int		 head; \
	int		 tail; \
	basetype data[(queue_size)]; \
}

/**
 * squeue_init - initializes named static queue. 
 * @struct_name: the structure name of declared static queue.
 * @queue_size:  the array size of queue.
 * 
 * Example:
 *		STRUCT_SQUEUE(int, 10) int_q;
 *		// Initializes declared static queue structure.
 *		SQUEUE_INIT(int_q);
 */
#define SQUEUE_INIT(struct_name) \
	do { \
		(struct_name).head = -1; \
		(struct_name).tail = -1; \
	} while (0)
/**
 * squeue_reset - reset queue to empty state.
 * @queue: static queue structure.
 */
#define squeue_reset(queue) SQUEUE_INIT((queue))
/**
 * squeue_is_empty - check if queue is empty.
 * @queue: static queue structure.
 * Return: bool, true if queue is empty, false if not empty.
 */
#define squeue_is_empty(queue) ((queue).head == -1)
/**
 * squeue_is_full - check if queue is full.
 * @queue: static queue structure.
 * Return: bool, true if queue is full, false if not full.
 */
#define squeue_is_full(queue) ((((queue).tail + 1) % squeue_size((queue))) == (queue).head)
/**
 * squeue_size - get size of static queue array.
 * @queue: static queue structure.
 * Return: size_t, size of static queue array.
 */
#define squeue_size(queue)     ARRAY_SIZE((queue).data)
/**
 * squeue_equeue - inserts element at front of queue.
 * @queue:   static queue structure.
 * @element: element to insert. Must be same type from call to NEW_SQUEUE.
 * Return:   bool, true on success, false if queue is full.
 */
#define squeue_enqueue(queue, element) \
({ \
	bool __ret = !squeue_is_full((queue)); \
	if (__ret) { \
		if (squeue_is_empty((queue))) { \
			(queue).head = 0; \
		} \
		(queue).tail = ((queue).tail + 1) % squeue_size(queue); \
		(queue).data[(queue).tail] = (element); \
	} \
	__ret; \
})
/**
 * squeue_front - get the front element of queue without removing.
 * @queue: static queue structure.
 * Return: basetype, front element of queue.
 */
#define squeue_front(queue) \
({ \
	typeof(queue.data[0]) __ret = 0; \
	if (!squeue_is_empty((queue))) { \
		__ret = (queue).data[(queue).head]; \
	} \
	__ret; \
})
/**
 * squeue_dequeue - deletes element from front of queue.
 * @queue: static queue structure.
 * Return: bool, true if deleted, false if not.
 */
#define squeue_dequeue(queue) \
({ \
	bool __ret = false; \
	if (!squeue_is_empty((queue))) { \
		__ret = true; \
		if ((queue).head == (queue).tail) { \
			squeue_reset((queue)); \
		} else { \
			(queue).head = ((queue).head + 1) % squeue_size(queue); \
		} \
	} \
	__ret; \
})
#endif /* STDMACRO_SQUEUE_H */
