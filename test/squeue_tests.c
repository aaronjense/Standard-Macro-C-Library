#include <stdmacro/squeue.h>
#include <assert.h>
#include <stdio.h>


int main(void) {
	int i;
	int pop;
	const int int_q_size = 10;

	/* test struct_squeue: bastype is int */
	STRUCT_SQUEUE(int, int_q_size) int_q;
	assert(sizeof(int_q.data[0]) == sizeof(int));

	/* test squeue_init: head and tail is 0 */
	SQUEUE_INIT(int_q);
	assert(int_q.head == -1 && int_q.tail == -1);

	/* test squeue_is_empty: true */
	assert(squeue_is_empty(int_q) == true);

	/* test squeue_is_full: false */
	assert(squeue_is_full(int_q) == false);

	/* test squeue_size: size == 10 */
	assert(squeue_size(int_q) == int_q_size);

	/* test squeue_enqueue: fill to max */
	for (i = 0; i < int_q_size; i++) {
		assert(squeue_enqueue(int_q, i) == true);
	}

	/* test squeue_is_full: true */
	assert(squeue_is_full(int_q) == true);

	/* test squeue_enqueue: push when full returns false */
	assert(squeue_enqueue(int_q, 0) == false);

	/* test squeue_dequeue: pop all elements, check value is correct */
	for (i = 0; i < int_q_size; i++) {
		assert(i == squeue_front(int_q));
		assert(squeue_dequeue(int_q) == true);
	}

	/* test squeue_is_empty: queue should be empty now */
	assert(squeue_is_empty(int_q) == true);

	/* test squeue_is_full: false */
	assert(squeue_is_full(int_q) == false);

	/* test squeue_dequeue: there should be no elements to remove */
	assert(squeue_dequeue(int_q) == false);

	/* test squeue_enqueue: fill to max */
	for (i = 0; i < int_q_size; i++) {
		assert(squeue_enqueue(int_q, i) == true);
	}

	/* test squeue_is_full: true */
	assert(squeue_is_full(int_q) == true);

	/* test squeue_enqueue: push when full returns false */
	assert(squeue_enqueue(int_q, 0) == false);

	/* test squeue_dequeue: pop all elements, check value is correct */
	for (i = 0; i < int_q_size; i++) {
		assert(i == squeue_front(int_q));
		assert(squeue_dequeue(int_q) == true);
	}

	/* test squeue_is_empty: queue should be empty now */
	assert(squeue_is_empty(int_q) == true);

	/* test squeue_is_full: false */
	assert(squeue_is_full(int_q) == false);

	/* test squeue_dequeue: there should be no elements to remove */
	assert(squeue_dequeue(int_q) == false);

	printf("PASSED\n");

	return 0;
}