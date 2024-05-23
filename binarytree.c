//binarytree.c: The implementation of the binary search tree specified in binarytree.h
// Author: Aidan Stoeffler

#include <stdlib.h>
#include "binarytree.h"

//createNode
treeNode* createNode(int ind, int val){
	//Allocate the memory.
	treeNode* newNode = (treeNode*) malloc(sizeof(treeNode));
	//Assign the index and value.
	newNode->index = ind;
	newNode->value = val;
	//Set the subtree pointers to point to NULL, since there does not exist any children yet.
	newNode->left = NULL;
	newNode->right = NULL;
	//Set the parent to NULL (used with the red-black implementation)
	newNode->parent = NULL;
	//Set the color of the node to red (used with the red-black implementation)
	newNode->color = 0;
	return(newNode);
}
//search
treeNode* search(treeNode* root, int ind){
	//Check for the following 4 cases, and divert accordingly.
	//Case 1: Root is equal to NULL.
	//Case 2: Root.index equals ind
	//Case 3: ind is less than root.index
	//Case 4: ind is greater than root.index
	if(root == NULL){
		//Case 1 happens, in which there is no node inside the tree that contains ind. Return the null pointer
		// NULL.
		return(NULL);

	}else if(root->index == ind){
		//Case 2 happens.
		// In this outcome, root is the node that contains ind, and it will be returned.
		return(root);
		

	}else if(ind < root->index){
		//Case 3 happens.
		// In this outcome, the left subtree may contain a node with index ind, if it exists in the tree.
		// Return a recursive call to search, but send root.left as the root parameter instead.
		return(search((root->left), ind));

	}else{
		//Case 4 happens.
		// In this outcome, if the tree contains a node with index ind, that node will be in the right subtree.
		//  Return a recursive call to search, but send root.right as the root parameter instead.
		return(search((root->right), ind));

	}
	return(NULL);

}

//insert
void insert(treeNode* root, treeNode* leaf){
	//Find the next location to search for the available spot.
	//Initialize a treeNode pointer named next.
	treeNode* next;
	// Case 1a: leaf.index <= root.index
	// Case 1b: leaf.index > root.index
	if(leaf->index <= root->index){
		//Case 1a is the outcome, and the leaf must be inserted in the left subtree.
		//Set next to root.left
		next = root->left;


	}else{
		//Case 1b is the outcome, and the leaf must be inserted in the right subtree.
		//Set next to root.right
		next = root->right;

	}
	//Next, check if next is an actual node in the tree and not a null value.
	// If so, recursively call insert, with next and leaf.
	// Otherwise, use another condition statement to determine where to insert leaf.
	if(next != NULL){
		insert(next, leaf);

	}else{
		if(leaf->index <= root->index){
			root->left = leaf;

		}else{
			root->right = leaf;

		}
		//Set leaf's parent pointer to root. (for use with rotations.)
		leaf->parent = root;

	}

}

//deleteTree
void deleteTree(treeNode* root){
	//Check if the left node does not equal NULL. If this is true, recursively call deleteTree on root.left
	if(root->left != NULL){
		deleteTree(root->left);

	}
	//Then, check if the right node does not equal NULL. Again, if this is true, recursively call deleteTree
	// on root.right.
	if(root->right != NULL){
		deleteTree(root->right);

	}
	//Finally, free root.
	free(root);

}
