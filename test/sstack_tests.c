#include <stdmacro/sstack.h>
#include <stdint.h>
#include <assert.h>

#define test_init(sk, size, basetype) \
	/* test stack basetype */ \
	assert(sizeof(sk.data[0]) == sizeof(basetype)); \
\
	/* test sstack_init: top is 0 */ \
	assert(sk.top == 0); \
\
	/* test sstack_is_empty: true */ \
	assert(sstack_is_empty(sk) == true); \
\
	/* test sstack_is_full: false */ \
	assert(sstack_is_full(sk) == false); \
\
	/* test sstack_size: size == size */ \
	assert(sstack_size(sk) == (size)); \

#define test_fill_and_empty(sk, size) \
({ \
	int __i; \
	/* test sstack_push: fill to max */ \
	for (__i = 0; __i < (size); __i++) { \
		assert(sstack_push(sk, __i) == true); \
	} \
\
	/* test sstack_is_full: true */ \
	assert(sstack_is_full(sk) == true); \
\
	/* test sstack_push: push when full returns false */ \
	assert(sstack_push(sk, 0) == false); \
\
	/* test sstack_pop: pop all elements, check value is correct */ \
	for (__i = (size) - 1; __i >= 0; __i--) { \
		assert(__i == sstack_peek(sk)); \
		assert(sstack_pop(sk) == true); \
	} \
\
	/* test sstack_is_empty: stack should be empty now */ \
	assert(sstack_is_empty(sk) == true); \
\
	/* test sstack_is_full: false */ \
	assert(sstack_is_full(sk) == false); \
\
	/* test sstack_pop: there should be no elements to remove */ \
	assert(sstack_pop(sk) == false); \
})

int main(void) {
	const int stack_size = 10;

	/* Test STRUCT_SSTACK with postponed named declaration */
	STRUCT_SSTACK(int, stack_size);
	struct sstack_int sk_int;

	STRUCT_SSTACK(double, stack_size);
	struct sstack_double sk_double;

	STRUCT_SSTACK(uint8_t, stack_size) sk_u8;

	SSTACK_INIT(sk_int);
	test_init(sk_int, stack_size, int);
	test_fill_and_empty(sk_int, stack_size);
	test_fill_and_empty(sk_int, stack_size);

	SSTACK_INIT(sk_double);
	test_init(sk_double, stack_size, double);
	test_fill_and_empty(sk_double, stack_size);
	test_fill_and_empty(sk_double, stack_size);

	return 0;
}