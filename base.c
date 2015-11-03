#include "base.h"
#include <stdio.h>
#include <stdlib.h>

void succeed(char *message) {
	printf("%s\n", message);
	return;
}

void fail(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void testBase() {
    succeed("Base module OK");
}



  



