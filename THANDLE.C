#include <stdio.h>
#include <dos.h>
#include <time.h>

void interrupt tmr();
void interrupt (*old)();

int count=-1;

void main()
{
	clrscr();
	old=getvect(0x08);
	setvect(0x08,tmr);
	while(inportb(0x60) != 1)
	{
	}
}

void interrupt tmr()
{
	time_t t1;
	struct tm *t2;
	t1=time(NULL);
	t2=localtime(&t1);
	count++;
	/*It's actually 18.2 but for our purposes 18 is good enough*/
	if(count >= 18)
	{
		printf("\b\b\b\b\b\b\b\b%.2d:%.2d:%.2d",t2->tm_hour,t2->tm_min,t2->tm_sec);
		count=-1;
	}
	(*old)();
}