#include <stdio.h>
void print(int v)
{
    printf("v = %d\n",v);
}
int add(int c, int d)
{
    int a;
    a = c + d;
    return a;
}
int main(void)
{
    int a = 2;
    int c = 3;
    int sum;
    sum = add(a, c);
    print(sum);
    return 0;
}
