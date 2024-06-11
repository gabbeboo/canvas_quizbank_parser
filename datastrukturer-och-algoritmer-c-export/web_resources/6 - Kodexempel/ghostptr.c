#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *p, *q;
	p = malloc(5);
	/* do stuff */
	free(p);
	if (*p == 0) {	/* Unsafe, but might not crash... */
		return -1;
	}
	q = malloc(7);
	if (*p == 0) {	/* This is really not what you want... */
		return -1;
	}
	free(q);
	return 0;
}
