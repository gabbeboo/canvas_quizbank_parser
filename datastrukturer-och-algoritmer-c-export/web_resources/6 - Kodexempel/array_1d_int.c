#include <stdlib.h>

#include "array_1d_int.h"

typedef struct array {
	int low;		// Lowest index
	int high;		// Highest index
	int *values;		// Actual values
	bool *has_values;	// Boolean
} array;

array *array_create(int low, int high)
{
	/* Allocate memory for array structure */
	array *a = malloc(sizeof(*a));
	/* Set limits */
	a->low = low;
	a->high = high;
	/* Allocate memory for array values */
	int n = high - low + 1;
	a->values = malloc(sizeof(a->values[0]) * n);
	a->has_values = calloc(n, sizeof(a->has_values[0]));

	return a;
}

void array_set_value(array * a, int pos, int val)
{
	int ix = pos - a->low;
	a->values[ix] = val;
	a->has_values[ix] = true;
}

int array_inspect_value(const array * a, int pos)
{
	int ix = pos - a->low;
	return a->values[ix];
}

bool array_has_value(const array * a, int pos)
{
	int ix = pos - a->low;
	return a->has_values[ix];
}

int array_high(const array * a)
{
	return a->high;
}

int array_low(const array * a)
{
	return a->low;
}

void array_kill(array * a)
{
	free(a->values);
	free(a->has_values);
	free(a);
}

void array_print(const array * a, array_callback print_func)
{
}
