#include <stdio.h>
#include <math.h>
#include <time.h>

void calcpi(long float iter);
void ppercent(long float a,long float b);

struct mt
{
	int hr;
	int mn;
	int sc;
};

void main()
{
	long float c;
	printf("\nEnter amount of iterations to perform (0 exits):");
	scanf("%lf",&c);
	if(c==0)
		exit(0);
	calcpi(c);
}

void calcpi(long float iter)
{
	long float x,y,a,b;
	clock_t st,et;
	int ttaken;
	x=1;
	b=0;
	st=clock();
	for(a=3;a<iter;a++)
	{
		y=1/a;
		if(b==0)
		{
			x=x-y;
			b=1;
		}
		else
		{
			x=x+y;
			b=0;
		}
		ppercent(a,iter);
		a++;
	}
	x=x*4;
	et=clock();
	printf("\b\b\b\bPI calculated with %.0f iterations is %.17f\n",iter,x);
	ttaken = (et-st) / CLK_TCK;
	printf("Calculated in %d seconds\n",ttaken);
	main();
}

void ppercent(long float ito, long float itd)
{
	long float pc;
	pc = ito / itd;
	pc = pc * 100;
	printf("\b\b\b\b%.0lf%%",pc);
}