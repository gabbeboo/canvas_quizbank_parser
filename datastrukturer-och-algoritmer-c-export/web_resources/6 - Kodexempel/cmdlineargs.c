#include <stdio.h>
int main(int argc, const char ** argv)
{
	printf("Number of parameters: %d\n", argc);
	for (int i = 0; i < argc; i++) {
		printf("Parameter %d: %s\n", i, argv[i]);
	}
	return 0;
}
