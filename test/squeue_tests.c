#include <stdmacro/squeue.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#define test_init(q, size, basetype) \
	/* test queue basetype */ \
	assert(sizeof(q.data[0]) == sizeof(basetype)); \
\
	/* test squeue_init: head and tail is -1 */ \
	assert(q.head == -1 && q.tail == -1); \
\
	/* test squeue_is_empty: true */ \
	assert(squeue_is_empty(q) == true); \
\
	/* test squeue_is_full: false */ \
	assert(squeue_is_full(q) == false); \
\
	/* test squeue_size: queue size == arg size */ \
	assert(squeue_size(q) == (size)); \

#define test_fill_and_empty(q, size) \
({ \
	int __i; \
	/* test squeue_enqueue: fill to max */ \
	for (__i = 0; __i < (size); __i++) { \
		assert(squeue_enqueue(q, __i) == true); \
	} \
\
	/* test squeue_is_full: true */ \
	assert(squeue_is_full(q) == true); \
\
	/* test squeue_enqueue: enqueue when full returns false */ \
	assert(squeue_enqueue(q, 0) == false); \
\
	/* test squeue_dequeue: remove all elements, check value is correct */ \
	for (__i = 0; __i < (size); __i++) { \
		assert(__i == squeue_front(q)); \
		assert(squeue_dequeue(q) == true); \
	} \
\
	/* test squeue_is_empty: queue should be empty now */ \
	assert(squeue_is_empty(q) == true); \
\
	/* test squeue_is_full: false */ \
	assert(squeue_is_full(q) == false); \
\
	/* test squeue_dequeue: there should be no elements to remove */ \
	assert(squeue_dequeue(q) == false); \
})

int main(void) {
	const int q_size = 10;

	/* Test STRUCT_SQUEUE with postponed named declaration */
	STRUCT_SQUEUE(int, q_size);
	struct squeue_int int_q;

	STRUCT_SQUEUE(double, q_size);
	struct squeue_double double_q;

	/* Test STRUCT_SQUEUE with immediate named declaration */
	STRUCT_SQUEUE(uint8_t, q_size) u8_q;

	SQUEUE_INIT(int_q);
	test_init(int_q, q_size, int);
	test_fill_and_empty(int_q, q_size);
	test_fill_and_empty(int_q, q_size);

	SQUEUE_INIT(double_q);
	test_init(double_q, q_size, double);
	test_fill_and_empty(double_q, q_size);
	test_fill_and_empty(double_q, q_size);

	SQUEUE_INIT(u8_q);
	test_init(u8_q, q_size, uint8_t);
	test_fill_and_empty(u8_q, q_size);
	test_fill_and_empty(u8_q, q_size);

	printf("PASSED: squeue_tests\n");

	return 0;
}