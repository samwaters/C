#include <time.h>
#include <stdio.h>
#include <conio.h>

struct mytime
{
	int hour;
	int min;
	int sec;
};

struct mytime *endtime();

void timerproc();
void timer(int interval);
void doexit();
float globvar;
struct mytime *thetime;
void main()
{
	/*int ival;
	printf("\nEnter a timer interval [milliseconds]:");
	scanf("%d",&ival);*/
	struct mytime *mt;
	mt = endtime();
	thetime = mt;
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
	int a,b,c;
	a = thetime->hour;
	b = thetime->min;
	c = thetime->sec;
	c--;
	if(c<0)
	{
		c=59;
		b--;
		if(b<0)
		{
			b=59;
			a--;
		}
	}
	thetime->hour = a;
	thetime->min = b;
	thetime->sec = c;
	printf("\b\b\b\b\b\b\b\b%.2d:%.2d:%.2d",a,b,c);
	if((a==0) && (b==0) && (c==0))
	{
		printf("\n\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\a\aTime Up\n");
		exit(0);
	}
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
}

struct mytime *endtime()
{
	struct mytime *timer;
	int a,b,c;
	int hr,mn,sc,tmp;
	printf("\nEnter hours:");
	scanf("%d",&a);
	printf("Enter minutes:");
	scanf("%d",&b);
	printf("Enter seconds:");
	scanf("%d",&c);
	hr = a;
	mn=0;
	sc=0;
	for(tmp=0;tmp<b;tmp++)
	{
		mn++;
		if(mn > 59)
		{
			mn = 0;
			hr++;
		}
	}
	for(tmp=0;tmp<c;tmp++)
	{
		sc++;
		if(sc > 59)
		{
			sc = 0;
			mn++;
			if(mn > 59)
			{
				mn = 0;
				hr++;
			}
		}
	}
	timer->hour = hr;
	timer->min = mn;
	timer->sec = sc + 1;
	return timer;
}
