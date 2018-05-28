#include <time.h>
#include <stdio.h>


void main()
{
	clock_t c1,c2;
	FILE * fn;
	float a,b,c;
	fn=fopen("c:/test.txt","w+");
	c1 = clock();
	for(a=0;a<100000;a++)
	{
		b=52*a;
		fprintf(fn,"%f",b);
	}
	c2=clock();
	c=(c2 - c1);
	printf("\nYour SAM Rating is %.2f",(1/c) * 1000);

}