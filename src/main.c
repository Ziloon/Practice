#include <stdio.h>
#include "swap.h"
#include "log.h"

int main(int argc, char const *argv[])
{
	int a = 1;
	int b = 2;
	logErr("hello git\r\n");
	logInfo("我想看电影\r\n");
	swap(&a, &b);
	logDbg("%d %d\r\n", a, b);
	return 0;
}