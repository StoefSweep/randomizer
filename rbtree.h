//rbtree.h: An implementation of the red-black BST for use with the randomizer. Serves as a decorator to binarytree.h, and aside from the createTree,
// insertNode, fixup, and deleteTree functions, this header file also defines leftRotate and rightRotate functions.
// Author: Aidan Stoeffler

#ifndef RBTREE_H
#define RBTREE_H
//Include the binarytree.h header file, since this is a decorator.
#include "binarytree.h"

//The data structure: Defined as either redBlackTree or rbTree, it contains only a single node, root.
typedef struct redBlackTree{
	treeNode* root;
}rbTree;


//leftRotate:
// Description: Performs a left rotation on node n in rbTree tree.
// Parameters:
// rbTree tree: The tree in which the rotation is performed.
// treeNode n: The node to rotate.
// Preconditions:
// n.right != NULL
// Postconditions:
// #n.right.parent == #n.parent AND n.parent == #n.right AND n.right == #n.right.left
// AND [n.right is now a direct child of the original n.parent]
void leftRotate(rbTree* tree, treeNode* n);

// rightRotate:
// Description: Performs a right rotation on node n in rbTree tree
// Parameters:
// rbTree: The tree in which the rotation is performed
// treeNode n: The node to rotate
// Preconditions:
// n.left != NULL
// Postconditions:
// #n.left.parent == #n.parent AND n.parent == #n.left AND n.left == #n.left.right
// AND [n.left is now a direct child of the original n.parent]
void rightRotate(rbTree* t, treeNode* n);

// createTree:
// Description: Creates a rbTree with the given treeNode to add.
// Parameters:
// treeNode newRoot: The root to add to the tree
// Preconditions:
// newRoot != NULL
// Postconditions:
// createTree.root == newRoot AND newRoot.color == 1
rbTree* createTree(treeNode* newRoot);

// searchTree:
// Description: Searches in the red-black tree for a given index, ind. Serves as a wrapper for search.
//.Parameters:
// rbTree tree: The tree to search in.
// int ind: The index to search for.
// Preconditions:
// tree != NULL
// Postconditions:
// searchTree == search(tree->root, ind)
treeNode* searchTree(rbTree* tree, int ind);

//fixup:
// Description: The fixup function for a red-black tree. Makes sure that all properties of a red-black tree are fulfilled.
// Parameters:
// rbTree tree: The tree to fix-up.
// treeNode n: The node to fix up.
// Preconditions:
// tree != NULL AND searchTree(tree, n->ind) != NULL
// Postconditions:
// [tree satisfies all 4 properties of a red-black tree]
void fixup(rbTree* tree, treeNode* n);

// rbInsert
// Description: Inserts the given node n into the red-black tree T and then fixes up n.
// Parameters:
// rbTree tree: The tree to insert into.
// treeNode* n: The node that will be inserted.
// Preconditions:
// tree != NULL AND n != NULL
// Postconditions:
// searchTree(tree, n->ind) != NULL AND [tree satisfies all 4 properties of a red-black tree]
void rbInsert(rbTree* tree, treeNode* n);

// deleteRBTree:
// Description: Deletes the tree. Serves as a wrapper for deleteTree
// Parameters:
// rbTree tree: The tree to delete
// Preconditions:
// tree != NULL
// Postconditions:
// tree == NULL
void deleteRBTree(rbTree* tree);
#endif
