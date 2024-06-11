#include <stdio.h>

void zero_histogram(int *hist)
{
	hist[0] = 0;
	hist[1] = 0;
	hist[2] = 0;
	hist[3] = 0;
	hist[4] = 0;
	hist[5] = 0;
	hist[6] = 0;
	hist[7] = 0;
	hist[8] = 0;
	hist[9] = 0;
}

void make_histogram(const char *msg, int *hist)
{
	for (int i = 0; msg[i] != 0; i++) {
		switch (msg[i]) {
		case '0':
			hist[0]++;
			break;
		case '1':
			hist[1]++;
			break;
		case '2':
			hist[2]++;
			break;
		case '3':
			hist[3]++;
			break;
		case '4':
			hist[4]++;
			break;
		case '5':
			hist[5]++;
			break;
		case '6':
			hist[6]++;
			break;
		case '7':
			hist[7]++;
			break;
		case '8':
			hist[8]++;
			break;
		case '9':
			hist[9]++;
			break;
		default:
			/* Do nothing */
			break;
		}
	}
}

void print_histogram(const int *hist)
{
	printf("0: %d\n", hist[0]);
	printf("1: %d\n", hist[1]);
	printf("2: %d\n", hist[2]);
	printf("3: %d\n", hist[3]);
	printf("4: %d\n", hist[4]);
	printf("5: %d\n", hist[5]);
	printf("6: %d\n", hist[6]);
	printf("7: %d\n", hist[7]);
	printf("8: %d\n", hist[8]);
	printf("9: %d\n", hist[9]);
}

int main(int argc, const char *argv[])
{
	const char *msg = "090-786 68 32";
	int hist[10];

	zero_histogram(hist);
	make_histogram(msg, hist);
	print_histogram(hist);

	return 0;
}
