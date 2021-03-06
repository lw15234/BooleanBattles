/*Contains basic test functions and forward declarations to use throughout
the rest of the game*/

#include "base.h"
#include <stdio.h>
#include <stdlib.h>

/*Print a success message*/
void succeed(char *message) {
	fprintf(stdout, "%s\n", message);
	return;
}

/*Print an error message and exit*/
void fail(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

/*Trivial test function for base module.
    Included for consistency with other modules*/
void testBase() {
    succeed("Base module OK");
}
