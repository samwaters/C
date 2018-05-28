#include <time.h>
#include <stdio.h>

void main()
{
	clock_t ck;
	int a;
	float b;
	char tmp[30];
	printf("Enter your name:");
	scanf("%s",tmp);
	ck = clock();
	a = ck;
	b = ck / CLK_TCK;
	printf("Well, %s, it took you %d clock ticks [%.5f sec] to enter your name\n",tmp,a,b);
}