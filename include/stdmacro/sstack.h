#if !defined(STDMACRO_SSTACK_H)
#define STDMACRO_SSTACK_H

#include <stdmacro/array_size.h>
#include <stdbool.h>

/**
 * struct_sstack - declares unnamed static stack structure.
 * @basetype:   the type of data in stack.
 * @stack_size: the array size of stack.
 * 
 * struct - metadata for static stack.
 * @top: index of top element in stack.
 * @data: the array that stores elements of stack.
 * 
 * Example:
 *		// Declare static stack structure, struct sstack_int, with stack size 10
 *		STRUCT_SSTACK(int, 10);
 *		struct sstack_int sk_int;
 *		// Declare static stack structure, struct sstack_double, and name it sk_double
 *		STRUCT_SQUEUE(double, 100) sk_double;
 * 
 * WARNING: must call SSTACK_INIT before using squeue API.
 */
#define STRUCT_SSTACK(basetype, stack_size) \
struct sstack_ ## basetype { \
	int top; \
	basetype data[(stack_size)]; \
}
/**
 * sstack_init - initializes named static stack. 
 * @stack: the structure name of declared static stack.
 * 
 * Example:
 *		STRUCT_SSTACK(int, 10) sk_int;
 *		// Initializes declared static stack structure.
 *		SSTACK_INIT(sk_int);
 */
#define SSTACK_INIT(stack) ((stack).top = 0)
/**
 * sstack_reset - reset stack to empty state.
 * @stack: static stack structure.
 */
#define sstack_reset(stack) SSTACK_INIT((stack))
/**
 * sstack_is_empty - check if stack is empty.
 * @stack: static stack structure.
 * Return: bool, true if empty, false if not empty.
 */
#define sstack_is_empty(stack) ((stack).top == 0)
/**
 * sstack_size - get the size of stack array.
 * @stack: static stack structure.
 * Return: int, size of stack data array.
 */
#define sstack_size(stack) (ARRAY_SIZE((stack).data))
/**
 * sstack_is_full - check if stack is full.
 * @stack: static stack structure.
 * Return: bool, true if stack is full, false if not full.
 */
#define sstack_is_full(stack) ((stack).top == sstack_size((stack)))
/**
 * sstack_push - add element to top of the stack.
 * @stack: static stack structure.
 * Return: bool, true if element added, false if stack is full.
 */
#define sstack_push(stack, element) \
({ \
	bool __ret = !sstack_is_full((stack)); \
	if (__ret) { \
		(stack).data[(stack).top++] = (element); \
	} \
	__ret; \
})
/**
 * sstack_pop - remove element from top of stack.
 * @stack: static stack structure.
 * Return: bool, true if element removed, false if stack is empty.
 */
#define sstack_pop(stack) \
({ \
	bool __ret = !sstack_is_empty((stack)); \
	if (__ret) { \
		(stack).top--; \
	} \
	__ret; \
})
/**
 * sstack_peek - get element from top of stack without removing it.
 * @stack: static stack structure.
 * Return: basetype, element from top of stack, 0 if stack is empty.
 */
#define sstack_peek(stack) \
({ \
	typeof((stack).data[0]) __ret = 0; \
	if (!sstack_is_empty((stack))) { \
		__ret = (stack).data[(stack).top - 1]; \
	} \
	__ret; \
})

#endif /* STDMACRO_SSTACK_H */