/*
 * main.c
 *
 *  Created on: Mar 15, 2019
 *      Author: Elijah Basile
 */

#include <stdio.h>
#include <stdlib.h>

#include "interface.h"

int main() {
	// required command that makes the 'scanf' and 'printf' work properly for user
	setvbuf(stdout,  NULL,  _IONBF,  0);

	// user menu
	menu();

	// exit successfully
	return 0;
}
