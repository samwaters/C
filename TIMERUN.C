#include <time.h>
#include <stdio.h>
#include <conio.h>

void timerproc();
void timer(int interval);
void doexit();
float globvar;

void main()
{
	/*int ival;
	printf("\nEnter a timer interval [milliseconds]:");
	scanf("%d",&ival);*/
	printf("Press Escape to Exit...\n");
	timer(1000);
}

void timer(int interval) /*Interval in ms*/
{
	clock_t ck; /*Clock ticks since program start*/
	float a,b;  /*a = Seconds since program start, b = Seconds Temp*/
	int c,ext; /*c = variable to keep timer going, ext = do we exit*/
	b = 0;
	c = 1;
	while(c > 0)
	{
		ck = clock();
		a = (ck / CLK_TCK);
		if(((a - b) * 1000) >= interval)
		{
			timerproc(); /*The proc to call every cycle*/
			b = a;
		}
		doexit();
	}

}

void timerproc()
{
	globvar++;
}

void doexit()
{
	int a;
	a = inportb(0x060);
	if(a < 100)
	{
		if(globvar >= 1)
		{
			printf("\nRunning for %.0f seconds",globvar);
			exit(0);
		}
	}
}