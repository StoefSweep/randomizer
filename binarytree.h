// binarytree.h
// Author: Aidan Stoeffler
// Description: This header file defines a binary search tree structure, and the search, insert, and freeMem functions.
// This function will also be used in the random.c randomizer.

#ifndef BINARYTREE_H
#define BINARYTREE_H

//The treeNode data structure: A data structure that contains the following information:
// index: The index of the node. This is its "key", and the BST will be sorted based on its value
// value: The value that the node has. This is its "value".
// left: A pointer to the left subtree of this node.
// right: A pointer to the right subtree of this node.
typedef struct tree_node{
	int index;
	int value;
	struct tree_node* left;
	struct tree_node* right;
	//The parent and color values are used for the red-black implementation.
	struct tree_node* parent;
	char color;
} treeNode;

//createNode: This function creates a treeNode, with the given index and value.
// Parameters:
// ind: The new node's index
// val: The new node's value
// Returns: A new treeNode whose index = ind and value = val
// Preconditions: None.
// Postconditions: createNode.index == ind AND createNode.value == val AND createNode.left == createNode.right == NULL
treeNode* createNode(int ind, int val);

// search: This function returns the treeNode that contains the node containing the desired index. Returns NULL
// if such a node does not exist in the tree.
// Parameters:
// root: The root node of the tree to search for the index.
// ind: The index to search for.
// Returns: The node that contains the index ind in the tree specified by root, if it exists
// Preconditions: root != NULL
// Postconditions: createNode = [the node in the tree that has the index ind, or NULL if it does not exist.]
treeNode* search(treeNode* root, int ind);

// insert: This function inserts a treeNode into the the tree that starts with the root specified.
// Parameters:
// root: The root node of the tree to insert the new node.
// leaf: The node to insert into the tree.
// Returns: Nothing
// Preconditions: root != NULL AND leaf != NULL
// Postconditions: [leaf is a descendant of root]
void insert(treeNode* root, treeNode* leaf);

// deleteTree: This function cleans the memory of the tree by recursively freeing its leaves in postfix order.
// Parameters:
// root: The root of the tree to free
// Returns: Nothing.
// Preconditions: root != NULL
// Postconditions: root == NULL
void deleteTree(treeNode* root);

#endif
