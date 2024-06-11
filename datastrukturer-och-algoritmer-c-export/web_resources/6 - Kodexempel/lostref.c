#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *p;
	p = malloc(5);
	/* do stuff, forget to call free */
	p = malloc(7);
	free(p);
	return 0;
}
