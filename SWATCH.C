#include <time.h>
#include <stdio.h>
#include <conio.h>

struct mytime
{
	int hour;
	int min;
	int sec;
	int ms;
};

void timerproc();
void timer(int interval);
void doexit();
float globvar;
struct mytime *thetime;
void main()
{
	thetime->hour=0;
	thetime->min=0;
	thetime->sec=0;
	thetime->ms=0;
	timer(1);
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
	int a,b,c,d;
	a = thetime->hour;
	b = thetime->min;
	c = thetime->sec;
	d = thetime->ms;
	d++;
	if(d > CLK_TCK)
	{
		d=0;
		c++;
		if(c > 59)
		{
			c=0;
			b++;
			if(b > 59)
			{
				b=0;
				a++;
			}
		}
	}
	thetime->hour = a;
	thetime->min = b;
	thetime->sec = c;
	thetime->ms = d;
	printf("\b\b\b\b\b\b\b\b\b\b\b\b%.2d:%.2d:%.2d.%.2d",a,b,c,d);
	globvar++;
}

void doexit()
{
	int a;
	a = inportb(0x060);
	if(a == 1)
	{
		if(globvar >= 1)
		{
			exit(0);
		}
	}
}