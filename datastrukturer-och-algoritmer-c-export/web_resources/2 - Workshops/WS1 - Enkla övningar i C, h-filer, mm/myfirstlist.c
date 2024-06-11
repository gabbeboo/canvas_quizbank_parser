#include <stdio.h>

int main(int argc, char **argv)
{
	int tal[100];
	int i;
	i = 0;
	do {
		scanf("%d", &tal[i]);
		i++;
	}
	while ((i < 100) && (tal[i - 1] >= 0));

	return 0;
}
