#include <stdio.h>
#include <stdlib.h>

int *new_int_array(int n)
{
	int *v;
	v = malloc(n * sizeof(int));
	return v;
}

int main(void)
{
	int *p, *q;
	p = new_int_array(10);
	/* Do stuff */
	q = new_int_array(10);
        /* Do more stuff */
        /* No deallocation! */
	return 0;
}
