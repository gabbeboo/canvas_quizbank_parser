#include <stdio.h>
#include "array_1d_int.h"

void zero_histogram(array * a)
{
	for (int i = array_low(a); i <= array_high(a); i++)
		array_set_value(a, i, 0);
}

void make_histogram(const char *msg, array * a)
{
	for (int i = 0; msg[i] != '\0'; i++)
		if (msg[i] >= array_low(a) && msg[i] <= array_high(a))
			array_set_value(a, msg[i],
					array_inspect_value(a,
							    msg[i]) + 1);
}

void print_histogram(const array * a)
{
	for (int i = array_low(a); i <= array_high(a); i++)
		if (array_inspect_value(a, i) > 0)
			printf("%c: %d\n", i, array_inspect_value(a, i));
}

int main(int argc, const char *argv[])
{
	const char *msg = "090-786 68 32";
	array *a = array_create('0', '9');

	zero_histogram(a);
	make_histogram(msg, a);
	print_histogram(a);

	array_kill(a);
	return 0;
}
