/*
 * bst.h
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#ifndef BST_H_
#define BST_H_

#include <stdbool.h>

// Structure Declarations

typedef struct node {
	void* dataPtr;
	struct node* left;
	struct node* right;
} NODE;

typedef struct {
	int count;
	int (*compare) (void* argu1, void* argu2);
	NODE* root;
} BST_TREE;

// Prototype Declarations

BST_TREE* BST_Create
			(int (*compare) (void* argu1, void* argu2));
BST_TREE* BST_Destroy (BST_TREE* tree);

bool	BST_Insert		(BST_TREE* tree, void* dataPtr);
bool	BST_Delete		(BST_TREE* tree, void* dltKey);
void*	BST_Retrieve	(BST_TREE* tree, void* keyPtr);
void	BST_Traverse	(BST_TREE* tree, void (*process) (void* dataPtr));

bool 	BST_Empty	(BST_TREE* tree);
bool	BST_Full	(BST_TREE* tree);
int		BST_Count	(BST_TREE* tree);

NODE*	_insert		(BST_TREE* tree, NODE* root, NODE* newPtr);
NODE*	_delete		(BST_TREE* tree, NODE* root, void* dataPtr, bool* success);
void*	_retrieve	(BST_TREE* tree, void* dataPtr, NODE* root);
void	_traverse	(NODE* root, void (*process) (void* dataPtr));
void	_destroy	(NODE* root);


#endif /* BST_H_ */



