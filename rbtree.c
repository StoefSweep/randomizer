//rbtree.c: An implementation of the red-black tree specified in rbtree.h.
//Author: Aidan Stoeffler

#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

rbTree* createTree(treeNode* newRoot){
	//First, dynamically allocate memory for a new rbTree, newTree.
	rbTree* newTree = (rbTree*) malloc(sizeof(rbTree));
	//Set newTree's root to newRoot.
	newTree->root = newRoot;
	//Then, color newRoot black.
	newTree->root->color = 1;
	//Return newTree
	return newTree;

}

treeNode* searchTree(rbTree* tree, int ind){
	//This is purely a wrapper function for search, so return search called on tree->root.
	return search(tree->root, ind);

}

void leftRotate(rbTree* tree, treeNode* n){
	//Create a pointer to the child node that will be swapped. In this case, it will be the right node.
	treeNode* child = n->right;
	//Initialize a temporary treeNode pointer that will be used for the swaps, temp.
	treeNode* temp;

	//Generally, the following values are swapped:
	// The parents of n and child are swapped.
	// n's right child and child's left child appear to be swapped. This can be done before the if statement.
	// Swap n's right child and child's left child.
	temp = child->left;
	child->left = n;
	n->right = temp;

	//Set the n->right->parent to n (if it exists)
	if(n->right != NULL){
		n->right->parent = n;
	}
	//There are three cases for this rotation:
	// Case 1: n is the root
	// Case 2: n is not the root.
	if(n == tree->root){
		//Case 1: n is the root. Set n->parent to child, and then set child->parent to NULL.
		n->parent = child;
		child->parent = NULL;
		//Set tree->root to point to child.
		tree->root = child;
	}else{
		//Case 2: In this case, n is somehow a indirect child of the root.
		//Swap the values of n->parent and child->parent.
		temp = n->parent;
		n->parent = child;
		child->parent = temp;
		// There are 2 further subcases:
		// Case 2a: n is the left child of temp
		// Case 2b: temp is the right child of temp
		if(n == temp->left){
			//Case 2a:
			//Set temp->left to point to child.
			temp->left = child;
		}else{
			//Case 2b:
			//Set temp->right to point to child.
			temp->right = child;
		}
	}
}

void rightRotate(rbTree* tree, treeNode* n){
	//Create a pointer to the child node that will be swapped. In this case, it will be the left node.
	treeNode* child = n->left;
	//Create a temporary node for the swapping.
	treeNode* temp;
	//Generally, the following values will be swapped and updated:
	// n's left node and child's right node will be swapped.
	// The parent pointers of those children nodes will be updated.
	// The parents of n and child will be swapped, and n's parent will have its child pointers updated to reflect
	// this.
	
	//Swap n's left node and child's right node.
	temp = n->left;
	n->left = child->right;
	child->right = n;
	//Update the affected parent pointers (if they exist).
	if(n->left != NULL){
		n->left->parent = n;

	}
	// There are 3 total variations on the process of swapping the parents. The cases for each are as follows:
	// Case 1: n is the root.
	// Case 2: n is a child, indirect or direct, of the root.
	if(n == tree->root){
		// Case 1:
		// n is the parent. Set n->parent to child and child->parent to NULL
		n->parent = child;
		child->parent = NULL;
		//Then, set tree->root to child.
		tree->root = child;

	}else{
		// Case 2:
		// Swap the values of n->parent and child->parent, and be sure to store the original value of n->parent
		temp = n->parent;
		n->parent = child;
		child->parent = temp;

		//From here, there are 2 sub-variations, following the following cases:
		// Case 2a: n was the left child of its parent at the start of this function
		// Case 2b: n was the right child of its parent at the start of this function.
		if(temp->left == n){
			//Case 2a:
			//Set temp->left to point to child
			temp->left = child;
		}else{
			//Case 2b:
			//Set temp->right to point to child.
			temp->right = child;
		}

	}
}

void fixup(rbTree* tree, treeNode* n){
	//Since the original function call starts right after an insert is made, this function will not be recursive.
	//Instead, a while loop will be used to loop up until the root is reached, making sure that the root is black
	// in every loop.
	//Before starting the loop, initialize a pointer that represent's n's "uncle" node.
	treeNode* uncle;
	// This function will loop until n's parent is black, or until n becomes the root.
	while(n->parent != NULL && n->parent->parent != NULL && n->parent->color == 0){
		//It is important to note that the root will always be black after each iteration, and therefore
		// the parent of the root will never be accessed.
		//There are two major variations, with 3 sub-variations for each. The major cases are as follows:
		// Case 1: n's parent is a left child of n's grandparent
		// Case 2: n's parent is a right child of n's grandparent.
		if(n->parent == n->parent->parent->left){
			//Case 1:
			//Set uncle to n->parent->parent->right.
			uncle = n->parent->parent->right;

			//From here, there are 3 sub-variations:
			//Case 1.1: n's parent and uncle are both red nodes
			//Case 1.2: n is a right child of n, and n's uncle is black.
			//Case 1.3: The base case.
			if(n->parent->parent->right != NULL && uncle->color == 0){
				//Case 1.1:
				//Recolor n's parent and uncle to both be black.
				n->parent->color = 1;
				uncle->color = 1;
				//Recolor n's grandparent to be red.
				n->parent->parent->color = 0;
				// Set n to its grandparent.
				n = n->parent->parent;
			}else{
				//Cases 1.2 and 1.3:
				if(n == n->parent->right){
					//Case 1.2
					// Set n to its parent, and then perform a left rotation on n.
					n = n->parent;
					leftRotate(tree, n);
				}
				//Case 1.3
				// Recolor n's parent to black, and recolor n's grandparent to red.
				n->parent->color = 1;
				n->parent->parent->color = 0;
				// Perform a right rotation on n's grandparent
				rightRotate(tree, n->parent->parent);

			}

		}else{
			//Case 2:
			// Set uncle to n->parent->parent->left
			uncle = n->parent->parent->left;
			// From here, there are three sub-variations:
			// Case 2.1: n's parent and uncle are both red nodes.
			// Case 2.2: n's uncle is a black node, and n is a left child.
			// Case 2.3: The base case.
			if(n->parent->parent->left != NULL && uncle->color == 0){
				//Case 2.1:
				//Recolor n's parent and uncle to black.
				n->parent->color = 1;
				uncle->color = 1;
				// Recolor n's grandparent to red.
				n->parent->parent->color = 0;
				// Set n to its grandparent.
				n = n->parent->parent;

			}else{
				//Cases 2.2 and 2.3:
				if(n == n->parent->left){
					//Case 2.2
					//Set n to its parent and perform a right rotation on n.
					n = n->parent;
					rightRotate(tree, n);

				}
				//Case 2.3
				// Recolor n's parent to black, and recolor n's grandparent to red.
				n->parent->color = 1;
				n->parent->parent->color = 0;
				// Perform a left rotation on n's grandparent.
				leftRotate(tree, n->parent->parent);


			}

		}
		//Set the color of the root to black.
		tree->root->color = 1;

	}

}

void rbInsert(rbTree* tree, treeNode* n){
	// Since this is a wrapper function for insert, call insert using tree->root and n as parameters.
	insert(tree->root, n);
	// Call fixup on tree and n
	fixup(tree, n);

}

void deleteRBTree(rbTree* tree){
	//Since this is a wrapper function for deleteTree, call deleteTree on tree->root.
	deleteTree(tree->root);

}
