/*
 * interface.h
 *
 *  Created on: Mar 15, 2019
 *      Author: Elijah Basile
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <stdio.h>

#include "bst.h"


typedef struct data {
	int key;
	void* test;
} DATA;

// user interface functions
void decisionTree(char*);
void menu();
void buildDecisionTree(BST_TREE*);
int compare (void*, void*);
FILE* getFile (BST_TREE*);
void applyDecisionTree(FILE*, BST_TREE*);

// testing functions
int inconclusive(char* string, int* loc);
int article(char* string, int* loc);
int individualDiabetic(char* string, int* loc);
int individualNotDiabetic(char* string, int* loc);
int otherDiabetic(char* string, int* loc);
int otherNotDiabetic(char* string, int* loc);
int initialTest (char* string, int* loc);
int possessiveTest (char* string, int* loc);
int sarcasmTest (char* string, int* loc);
int articleTest (char* string, int* loc);
int individualTest (char* string, int* loc);
int negativeTest (char* string, int* loc);

#endif /* INTERFACE_H_ */
