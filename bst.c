/*
 * bst.c
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

BST_TREE* BST_Create (int (*compare) (void* argu1, void* argu2)) {
	// local definitions
	BST_TREE* tree;

	// statements
	tree = (BST_TREE*) malloc (sizeof (BST_TREE));
	if (tree) {
		tree->root = NULL;
		tree->count = 0;
		tree->compare = compare;
	} // if

	return tree;
} // BST_Create

bool BST_Insert (BST_TREE* tree, void* dataPtr) {
	// local definitions
	NODE* newPtr;

	// statements
	newPtr = (NODE*)malloc(sizeof(NODE));
	if (!newPtr)
		return false;

	newPtr->right = NULL;
	newPtr->left = NULL;
	newPtr->dataPtr = dataPtr;

	if (tree->count == 0)
		tree->root = newPtr;
	else
		_insert(tree,tree->root,newPtr);

	(tree->count)++;
	return true;
} // BST_Insert

NODE* _insert (BST_TREE* tree, NODE* root, NODE* newPtr) {
	// statements
	if (!root)
		// if NULL tree
		return newPtr;

	// locate null subtree for insertion
	if (tree->compare(newPtr->dataPtr,root->dataPtr) < 0) {
		root->left = _insert(tree,root->left,newPtr);
		return root;
	} // new < node
	else // new data >= root data
	{
		root->right = _insert(tree, root->right, newPtr);
		return root;
	} // else new data >= root data
	return root;
}

bool BST_Delete (BST_TREE* tree, void* dltKey) {
	// local definitions
	bool success;
	NODE* newRoot;

	// statements
	newRoot = _delete(tree, tree->root, dltKey, &success);

	if (success) {
		tree->root = newRoot;
		(tree->count)--;
		if (tree->count == 0)
			// tree now empty
			tree->root = NULL;
	} // if
	return success;
}

NODE* _delete (BST_TREE* tree, NODE* root, void* dataPtr, bool* success) {
	// local definitions
	NODE* dltPtr;
	NODE* exchPtr;
	NODE* newRoot;
	void* holdPtr;

	// statements
	if (!root) {
		*success = false;
		return NULL;
	} // if

	if (tree->compare(dataPtr, root->dataPtr) < 0)
		root->left = _delete (tree, root->left, dataPtr, success);
	else if (tree->compare(dataPtr, root->dataPtr) > 0)
		root->right = _delete(tree, root->right, dataPtr, success);
	else { // delete node found -- test for leaf node
		dltPtr = root;
		if (!root->left) { // no left subtree
			free (root->dataPtr); // data memory
			newRoot = root->right;
			free (dltPtr); // BST node
			*success = true;
			return newRoot; // base case
		} // if true
		else {
			if (!root->right) { // only left subtree
				newRoot = root->left;
				free(dltPtr);
				*success = true;
				return newRoot; // base case
			} // if
			else { // delete node has two subtrees
				exchPtr = root->left;
				// find largest noe on left subtree
				while (exchPtr->right)
					exchPtr = exchPtr->right;

				//exchange data
				holdPtr = root->dataPtr;
				root->dataPtr = exchPtr->dataPtr;
				exchPtr->dataPtr = holdPtr;
				root->left = _delete(tree, root->left, exchPtr->dataPtr, success);
			} // else
		}
	} // node found
	return root;
} // _delete

void* BST_Retrieve (BST_TREE* tree, void* ketPtr) {
	// statements
	if (tree->root)
		return _retrieve (tree, ketPtr, tree->root);
	else
		return NULL;
} // BST_Retrieve

void* _retrieve (BST_TREE* tree, void* dataPtr, NODE* root) {
	if (root) {
		if (tree->compare(dataPtr,root->dataPtr) < 0)
			return _retrieve (tree, dataPtr, root->left);
		else if (tree->compare(dataPtr, root->dataPtr) > 0)
			return _retrieve (tree, dataPtr, root->right);
		else
			// found equal key
			return root->dataPtr;
	} else // data not in tree
		return NULL;
} // _retrieve

void BST_Traverse (BST_TREE* tree, void (*process) (void* dataPtr)) {
	_traverse (tree->root, process);
	return;
}

void _traverse (NODE* root, void (*process) (void* dataPtr)) {
	// statements
	if (root) {
		_traverse (root->left, process);
		process (root->dataPtr);
		_traverse (root->right, process);
	} // if
	return;
} // _traverse

bool BST_Emptry (BST_TREE* tree) {
	// statements
	return (tree->count == 0);
} // BST_Empty

bool BST_Full (BST_TREE* tree) {
	// local definitions
	NODE* newPtr;

	// statements
	newPtr = (NODE*)malloc(sizeof(*(tree->root)));
	if (newPtr) {
		free (newPtr);
		return false;
	} // if
	else
		return true;
} // BST_Full

int BST_Count (BST_TREE* tree) {
	// statements
	return (tree->count);
} // BST_Count

BST_TREE* BST_Destroy (BST_TREE* tree) {
	// statements
	if (tree)
		_destroy (tree->root);

	// All nodes deleted. free structure
	free (tree);
	return NULL;
} // BST_Destroy

void _destroy (NODE* root) {
	// statements
	if (root) {
		_destroy (root->left);
		free (root->dataPtr);
		_destroy(root->right);
		free (root);
	} // if
	return;
} // _destroy











