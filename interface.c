/*
 * interface.c
 *
 *  Created on: Mar 15, 2019
 *      Author: Elijah Basile
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "interface.h"
#include "bst.h"

#define INCONCLUSIVE 0
#define ARTICLE -1
#define IDIABETIC -2
#define INDIABETIC -3
#define ODIABETIC -4
#define ONDIABETIC -5

#define UNDETERMINED 3

#define FALSE 1
#define TRUE 2

void menu () {
	printf("=== Decision Tree Program ===\n\n");

	BST_TREE* tree = BST_Create(*compare);

	FILE* fptr = getFile(tree);

	applyDecisionTree(fptr,tree);
}

void applyDecisionTree(FILE* fin, BST_TREE* tree) {
	int result;
	char line[500];
	int loc;

	FILE* fout = fopen("output.csv","w");


	while (!feof(fin)) {
		NODE* curr = tree->root;
		result = UNDETERMINED;

		// get line from file
		fgets(line,500,fin);
		char* location = line;

		// jumping from tab to tab
		int counter = 0;
		while (counter < 2) {
			if (*location == 9)
				counter++;
			location++;
		}

		// copy contents of line onto testing line -- only testing text portion
		int marker = 0;
		char testLine[500];
		while (*location != 9) {
			testLine[marker] = *location;

			// increment
			marker++;
			location++;
		}
		testLine[marker] = '\0';

		while (result > 0) {
			// retrieve testing function
			DATA* data = (DATA *)curr->dataPtr;
			int (*test)(char*,int*) = data->test;

			// get result of test
			result = (*test)(testLine,&loc);
			if (result == TRUE)
				curr = curr->right;
			else if (result == FALSE)
				curr = curr->left;
			else
				break;
		}

		// print results to output file
		switch (result) {
			case UNDETERMINED:
				strcat(line, "	ERROR\n");
				break;
			case INCONCLUSIVE:
				strcat(line, "	INCONCLUSIVE\n");
				break;
			case ARTICLE:
				strcat(line, "	ARTICLE\n");
				break;
			case IDIABETIC:
				strcat(line, "	INDIVIDUAL DIABETIC\n");
				break;
			case INDIABETIC:
				strcat(line, "	INDIVIDUAL NOT DIABETIC\n");
				break;
			case ODIABETIC:
				strcat(line, "	OTHER PERSON DIABETIC\n");
				break;
			case ONDIABETIC:
				strcat(line, "	OTHER PERSON NOT DIABETIC\n");
				break;
		}
		fputs(line,fout);
	}
	fclose (fout);
	fclose (fin);
}

FILE* getFile(BST_TREE* tree) {
	FILE* fptr;
	char filename[256];
	bool isValid = false;
	char choice;

	do {
		fflush(stdin);
		printf("Enter the CSV file you wish to apply the decision tree to.\n");
		scanf("%s",filename);
		if (!(fptr = fopen(filename,"r"))) {
			printf("******* File Not Found *******\n");
			printf("e:		Enter a new file name \n");
			printf("q:		Quit this Menu.		  \n");
			while (!isValid) {
				isValid = true;
				fflush(stdin);
				choice = getchar();
				switch (choice) {
					case 'e':
						break;
					case 'q':
						printf("Exited successfully.\n");
						exit(0);
					default:
						printf("Enter valid input.\n");
						isValid = false;
				}
			}
		} else
			break;
	} while (true);
	buildDecisionTree(tree);
	return fptr;
}

void buildDecisionTree(BST_TREE* tree) {
	int order[15] = {2,1,4,3,14,12,15,8,13,6,10,5,7,9,11};
	for (int i = 0 ; i < 15 ; i++) {
		int count = order[i];
		void* toBeInserted = (void*)malloc(sizeof(DATA));
		((DATA *)toBeInserted)->key = count;
		switch (count) {
			case 1:
				((DATA *)toBeInserted)->test = &inconclusive;
				break;
			case 2:
				((DATA *)toBeInserted)->test = &initialTest;
				break;
			case 3:
				((DATA *)toBeInserted)->test = &inconclusive;
				break;
			case 4:
				((DATA *)toBeInserted)->test = &possessiveTest;
				break;
			case 5:
				((DATA *)toBeInserted)->test = &otherDiabetic;
				break;
			case 6:
				((DATA *)toBeInserted)->test = &negativeTest;
				break;
			case 7:
				((DATA *)toBeInserted)->test = &otherNotDiabetic;
				break;
			case 8:
				((DATA *)toBeInserted)->test = &individualTest;
				break;
			case 9:
				((DATA *)toBeInserted)->test = &individualDiabetic;
				break;
			case 10:
				((DATA *)toBeInserted)->test = &negativeTest;
				break;
			case 11:
				((DATA *)toBeInserted)->test = &individualNotDiabetic;
				break;
			case 12:
				((DATA *)toBeInserted)->test = &articleTest;
				break;
			case 13:
				((DATA *)toBeInserted)->test = &article;
				break;
			case 14:
				((DATA *)toBeInserted)->test = &sarcasmTest;
				break;
			case 15:
				((DATA *)toBeInserted)->test = &inconclusive;
				break;

		}
		BST_Insert(tree,toBeInserted);
	}
}

int inconclusive(char* string, int* loc) {
	return INCONCLUSIVE;
}

int article(char* string, int* loc) {
	return ARTICLE;
}

int individualDiabetic(char* string, int* loc) {
	return IDIABETIC;
}

int individualNotDiabetic(char* string, int* loc) {
	return INDIABETIC;
}

int otherDiabetic(char* string, int* loc) {
	return ODIABETIC;
}

int otherNotDiabetic(char* string, int* loc) {
	return ONDIABETIC;
}

int initialTest (char* string, int* loc) {
	char* curr = string;
	int count = 0;
	if (strlen(string) < 8)
		return FALSE;
	while (count != strlen(string) - 8 && *curr != '\0') {
		count++;
		if (strncasecmp(curr,"diabetic",8) == 0 || strncasecmp(curr,"diabetes",8) == 0) {
			*loc = count;
			return TRUE;
		}
		curr++;
	}
	return FALSE;
}

int possessiveTest (char* string, int* loc) {
	char* curr = string;
	int count = 0;
	if (strlen(string) < 2)
		return FALSE;
	while (count != *loc - 2 && *curr != '\0') {
		count++;
		if (strncasecmp(curr,"\'s ",3) == 0 || strncasecmp(curr," is ",4) == 0 || strncmp(curr," has ",5) == 0 || strncmp(curr," have ",6) == 0 || strncmp(curr," am ",4) == 0) {
			return TRUE;
		}
		if (strncasecmp(curr," r ",3) == 0)
			return TRUE;
		curr++;
	}
	return FALSE;
}

int sarcasmTest (char* string, int* loc) {
	char* curr = string;
	int count = 0;
	if (strlen(string) < 5)
		return FALSE;
	while (count != *loc - 5 && *curr != '\0') {
		count++;
		if (strncasecmp(curr,"gonna",5) == 0 || strncasecmp(curr,"going to",8) == 0)
			return TRUE;
		curr++;
	}
	return FALSE;
}

int articleTest (char* string, int* loc) {
	char* curr = string;
	int count = 0;
	if (strlen(string) < 3)
		return FALSE;
	while (count != *loc - 3 && *curr != '\0') {
		count++;
		if (strncasecmp(curr,"you",3) == 0 || strncasecmp(curr,"someone",7) == 0 || strncasecmp(curr," u ",3) == 0)
			return TRUE;
		curr++;
	}
	return FALSE;
}

int individualTest (char* string, int* loc) {
	char* curr = string;
	int count = 0;
	if (strlen(string) < 2)
		return FALSE;
	while (count != *loc - 2 && *curr != '\0') {
		if (count == 0) {
			if (strncasecmp(curr,"I ",2))
				return TRUE;
		} else {
			if (strncasecmp(curr," I ",3) == 0)
				return TRUE;
		}
		count++;
		curr++;
	}
	return FALSE;
}

int negativeTest (char* string, int* loc) {
	char* curr = string;
	int count = 0;
	if (strlen(string) < 3)
		return FALSE;
	while (count != strlen(string) - 3 && *curr != '\0') {
		if (strncasecmp(curr,"not",3) == 0 || strncasecmp(curr,"false",5) == 0 || strncmp(curr,"negative",8) == 0)
			return TRUE;
		count++;
		curr++;
	}
	return FALSE;
}







int compare (void* argu1, void* argu2) {
	if (!argu2)
		return 1;
	if (((DATA *)argu1)->key > ((DATA *)argu2)->key)
		return 1;
	if (((DATA *)argu1)->key < ((DATA *)argu2)->key)
		return -1;
	return 0;
}
