#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *p, *q;
	p = malloc(5);
	/* do stuff */
	q = p;
	free(q);	/* this is ok */
	return 0;
}
