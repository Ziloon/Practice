#include <stdio.h>
#include "swap.h"

int main(int argc, char const *argv[])
{
	int a = 1;
	int b = 2;
	printf("hello git\r\n");
	printf("我想看电影\r\n");
	swap(&a, &b);
	printf("%d %d\r\n", a, b);
	return 0;
}