#include <stdmacro/sbtree.h>
#include <assert.h>
#include <math.h>


#define test_set_tree(sbt) \
({ \
	int i; \
	int parent_index; \
	int data; \
\
	assert(sbtree_is_empty((sbt)) == true); \
	assert(sbtree_is_full((sbt)) == false); \
\
	data = 0; \
	assert(sbtree_set_root((sbt), data++) == true); \
\
	parent_index = 0; \
	for (i = 0; i < sbtree_max_height((sbt)); i++) { \
		assert(true == sbtree_set_left((sbt), data++, parent_index)); \
		assert(true == sbtree_set_right((sbt), data++, parent_index++)); \
\
		assert((sbt).nodes[i].data   == i); \
		assert((sbt).nodes[i+1].data == i+1); \
	} \
\
	assert(sbtree_is_full((sbt)) == true); \
	assert(sbtree_is_empty((sbt)) == false); \
	assert(sbtree_set_root((sbt), data++) == false); \
\
	parent_index = 0; \
	for (i = 0; i < sbtree_max_height((sbt)); i++) { \
		assert(false == sbtree_set_left((sbt), data++, parent_index)); \
		assert(false == sbtree_set_right((sbt), data++, parent_index++)); \
\
		assert((sbt).nodes[i].data   == i); \
		assert((sbt).nodes[i+1].data == i+1); \
	} \
})

#define test_delete_tree(sbt) \
({ \
	int i; \
	int parent_index; \
	int data; \
\
	assert(sbtree_is_empty((sbt)) == false); \
	assert(sbtree_is_full((sbt)) == true); \
\
	data = 0; \
\
	parent_index = 0; \
	assert(true == sbtree_del_root((sbt))); \
	for (i = 0; i < sbtree_max_height((sbt)); i++) { \
		assert(true == sbtree_del_left((sbt), parent_index)); \
		assert(true == sbtree_del_right((sbt),parent_index++)); \
	} \
\
	assert(sbtree_is_full((sbt)) == false); \
	assert(sbtree_is_empty((sbt)) == true); \
\
	assert(false == sbtree_del_root((sbt))); \
})

int main(void) {
	const int total_nodes = pow(2, 3) - 1;
	STRUCT_SBTREE(int, total_nodes);
	struct sbtree_int sbt_int;

	SBTREE_INIT(sbt_int);

	test_set_tree(sbt_int);

	test_delete_tree(sbt_int);

	return 0;
}