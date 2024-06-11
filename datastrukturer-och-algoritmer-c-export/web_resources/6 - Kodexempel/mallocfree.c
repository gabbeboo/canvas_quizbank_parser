#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *p = malloc(10 * sizeof(int));
	/* do stuff */
	free(p);
	return 0;
}
