#include <stdio.h>
#include <time.h>

void reboot();
void timerproc();
void timer(int interval);

struct mytime
{
	int hour;
	int min;
	int sec;
};

struct mytime *tleft;

void main()
{
	tleft->hour=0;
	tleft->min=0;
	tleft->sec=89;
	printf("\nPress a key or your computer will reboot in 90 seconds");
	timer(1000);
}

void timer(int interval)
{
	clock_t ck;
	float a,b;
	int c;
	b=0;
	c=1;
	while(c > 0)
	{
		ck = clock();
		a = (ck / CLK_TCK);
		outportb(0x60,0x20); /*You are helpless now ha ha ha ha*/
		if(((a - b) * 1000) >= interval)
		{
			timerproc();
			b = a;
		}
	}
}


void timerproc()
{
	int s;
	s = tleft->sec;
	printf("\b\b\b\b\b\b\b\b\b\b");
	printf("%.2d seconds",s);
	s = s - 1;
	if(s < 0)
	{
		printf("\nOh well. You didn't stop the program.\n");
		reboot();
	}
	tleft->sec = s;
}

void reboot()
{
	outportb(0xCF9,4);
	outportb(0xCF9,2);
}