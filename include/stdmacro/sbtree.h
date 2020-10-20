#if !defined(STDMACRO_SBTREE_H)
#define STDMACRO_SBTREE_H

#include <stdmacro/array_size.h>
#include <stdbool.h>

/**
 * struct_sbtree - declares unnamed static binary tree structure.
 * @basetype:   the type of data in binary tree node.
 * @queue_size: the array size of binary tree.
 * 
 * struct sbtree_<basetype> - metadata for static binary tree.
 * @node_cnt: the amount of node entries in binary tree.
 * 
 * struct sbtree_node_<basetype> - metadata for binary tree node.
 * @idx: -1 if not in tree, else stores idx of array location.
 * @data: stores node data entry.
 * 
 * Example:
 *		// Declare static binary tree structure, struct sbtree_int, with array size 7
 *		STRUCT_SBTREE(int, 2^3 - 1);
 *		struct sbtree_int sbt_int;
 *		// Declare static binary tree structure, struct sbtree_double, and name it sbt_double
 *		STRUCT_SBTREE(double, 100) sbt_double;
 * 
 * WARNING: must call SBTREE_INIT before using squeue API.
 */
#define STRUCT_SBTREE(basetype, total_nodes) \
struct sbtree_ ## basetype { \
	int node_cnt; \
	struct sbtree_node_ ## basetype { \
		int idx; \
		basetype data; \
	} nodes[(total_nodes)]; \
}
/**
 * sbtree_init - initializes named static binary tree. 
 * @btree: the structure name of declared static queue.
 * 
 * Example:
 *		STRUCT_SBTREE(int, 10) sbt_int;
 *		// Initializes declared static binary tree structure.
 *		SBTREE_INIT(sbt_int);
 */
#define SBTREE_INIT(btree) \
	do { \
		int __i; \
		(btree).node_cnt = 0; \
		for (__i = 0; __i < sbtree_size((btree)); __i++) { \
			(btree).nodes[__i].idx = -1; \
		} \
	} while (0)
/**
 * PRIVATE: __sbtree_node_is_entry - returns if node was set into tree.
 * @sbtree_node: a node from a declared binary tree.
 * 
 * Return: true if node is in tree, false if not set.
 */
#define __sbtree_node_is_entry(sbtree_node) ((sbtree_node).idx != -1)
/**
 * sbtree_size - get the size of binary tree array.
 * @btree: binary tree structure.
 * 
 * Return: size of binary tree array.
 */
#define sbtree_size(btree) (ARRAY_SIZE((btree).nodes))
/**
 * sbtree_max_height - get the height of root node in binary tree.
 * @btree: binary tree structure.
 * 
 * Return: height of root node.
 */
#define sbtree_max_height(btree) log2(sbtree_size(btree))
/**
 * sbtree_tree_is_full - check if binary tree array is full.
 * @btree: binary tree structure.
 * 
 * Return: bool, true if array has been filled, false if not filled.
 */
#define sbtree_is_full(btree) ((btree).node_cnt == sbtree_size((btree)))
/**
 * sbtree_is_empty - check if binary tree has no nodes, including root.
 * @btree: binary tree structure.
 * 
 * Return: bool, true if no nodes set, false if at least root is set.
 */
#define sbtree_is_empty(btree) ((btree).node_cnt == 0)
/**
 * PRIVATE: __sbtree_is_valid_index - check if index is within bounds of array.
 * @btree: binary tree structure.
 * 
 * Return: bool, true if valid, false if index exceeds array bounds.
 */
#define __sbtree_is_valid_index(btree, index) ((index) < sbtree_size((btree)))
/**
 * PRIVATE: __sbtree_set_node - set the element at node index.
 * @btree:   binary tree structure.
 * @element: data to place in node.
 * @index:   index of node to set in tree.
 * 
 * Return: bool, true if successful, false if invalid index, tree is full or node was already set.
 */
#define __sbtree_set_node(btree, element, index) \
({ \
	bool __ret = __sbtree_is_valid_index((btree), (index)); \
	__ret = __ret && !sbtree_is_full((btree)); \
	__ret = __ret && (__sbtree_node_is_entry((btree).nodes[(index)]) == false); \
	if (__ret) { \
		(btree).nodes[(index)].idx = (index); \
		(btree).nodes[(index)].data = (element); \
		(btree).node_cnt++; \
	} \
	__ret; \
})
/**
 * PRIVATE: __sbtree_del_node - delete the node at index.
 * @btree: binary tree structure.
 * @index: index of node to delete from tree.
 * 
 * Return: bool, true if node delete, false if invalid index or tree is empty.
 */
#define __sbtree_del_node(btree, index) \
({ \
	bool __ret = __sbtree_is_valid_index((btree), (index)); \
	__ret = __ret && !sbtree_is_empty((btree)); \
	if (__ret) { \
		(btree).nodes[(index)].idx = -1; \
		(btree).node_cnt--; \
	} \
	__ret; \
})
/**
 * sbtree_del_root - delete root of tree.
 * @btree: binary tree structure.
 * 
 * Return: bool, true if root delete, false if tree is empty.
 */
#define sbtree_del_root(btree) __sbtree_del_node((btree), 0)
/**
 * sbtree_del_left - delete left child of parent at index.
 * @btree: binary tree structure.
 * @index: the index of parent.
 * 
 * Return: true if left child node deleted, false if invalid index or tree is empty.
 */
#define sbtree_del_left(btree, index) \
({ \
	int __idx = (2 * (index)) + 1; \
	__sbtree_del_node((btree), __idx); \
})
/**
 * sbtree_del_right - delete right child of parent at index.
 * @btree: binary tree structure.
 * @index: the index of parent.
 * 
 * Return: true if right child node delete, false if invalid index or tree is empty.
 */
#define sbtree_del_right(btree, index) \
({ \
	int __idx = (2 * (index)) + 2; \
	__sbtree_del_node((btree), __idx); \
})
/**
 * sbtree_set_root - add the root node to empty tree.
 * @btree: binary tree structure.
 * @data:  data to place into root node.
 * 
 * Return: true if root set, false if already set.
 */
#define sbtree_set_root(btree, data) __sbtree_set_node((btree), (data), 0)
/**
 * sbtree_set_left - add left child to parent at index.
 * @btree: binary tree structure.
 * @data:  data to add to left child node.
 * @index: index of parent.
 * 
 * Return: true if left node set, false if already set, invalid index or tree is full.
 */
#define sbtree_set_left(btree, data, index) \
({ \
	int __idx = (2 * (index)) + 1; \
	 __sbtree_set_node((btree), (data), __idx); \
})
/**
 * sbtree_set_right - add right child to parent at index.
 * @btree: binary tree structure.
 * @data:  data to add to right child node.
 * @index: index of parent.
 * 
 * Return: true if left node set, false if already set, invalid index or tree is full.
 */
#define sbtree_set_right(btree, data, index) \
({ \
	int __idx = (2 * (index)) + 2; \
	 __sbtree_set_node((btree), (data), __idx); \
})

#endif /* STDMACRO_SBTREE_H */