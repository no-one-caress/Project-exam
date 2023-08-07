#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAX_ERR 4

static char* p[] = { "",
					"incorrect input",
					"open file",
					"memory problem",
					"other",
};
void error(int nr, char* str)
{
	int k;
	k = nr >= MAX_ERR ? MAX_ERR : nr;
	fprintf(stdout, "Error{%d} %s - %s\n", nr, p[k], str);	//stderr
	//exit(nr);
}