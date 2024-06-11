#include <stdio.h>
#include <stdlib.h>

void zero_histogram(int *hist, char low, char high)
{
	for (char i = low; i <= high; i++)
		hist[i - low] = 0;
}

void make_histogram(const char *msg, int *hist, char low, char high)
{
	const char *p;
	for (p = msg; *p; p++)
		if (*p >= low && *p <= high)
			hist[*p - low]++;
}

void print_histogram(const int *hist, char low, char high)
{
	for (char i = low; i <= high; i++)
		if (hist[i - low] > 0)
			printf("%c: %d\n", i, hist[i - low]);
}

int main(int argc, const char *argv[])
{
	const char *msg = "090-786 68 32";
	char low = '0';
	char high = '9';
	int n = high - low + 1;
	int *hist = malloc(n * sizeof(*hist));

	zero_histogram(hist, low, high);
	make_histogram(msg, hist, low, high);
	print_histogram(hist, low, high);

	free(hist);
	return 0;
}
