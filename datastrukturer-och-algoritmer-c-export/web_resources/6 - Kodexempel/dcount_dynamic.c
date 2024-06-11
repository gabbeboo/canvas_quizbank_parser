#include <stdio.h>
#include <stdlib.h>

void zero_histogram(int *hist)
{
	for (int i = 0; i < 10; i++)
		hist[i] = 0;
}

void make_histogram(const char *msg, int *hist)
{
	for (int i = 0; msg[i] != '\0'; i++)
		if (msg[i] >= '0' && msg[i] <= '9')
			hist[msg[i] - '0']++;
}

void print_histogram(const int *hist)
{
	for (int i = 0; i < 10; i++)
		if (hist[i] > 0)
			printf("%d: %d\n", i, hist[i]);
}

int main(int argc, const char *argv[])
{
	const char *msg = "090-786 68 32";
	int n = 10;
	int *hist = malloc(n * sizeof(int)); /* reserveration */

	zero_histogram(hist);
	make_histogram(msg, hist);
	print_histogram(hist);

	free(hist);                          /* återlämning */
	return 0;
}
