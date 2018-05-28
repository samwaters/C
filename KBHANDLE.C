#include <stdio.h>
#include <dos.h>

void interrupt myhandle();
void interrupt (*old)();

int lk;

void main()
{
	old = getvect(0x09);
	setvect(0x09,myhandle);
	while(inportb(0x60) != 1)
	{
	}
}

void interrupt myhandle()
{
	int a;
	a=inportb(0x60);
	if(a < 100)
	{
		if(a != lk)
		{
			printf("%d",a);
		}
	}
	lk=a;
	(*old)();
}