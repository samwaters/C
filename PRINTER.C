#include <stdio.h>
#include <ctype.h>

#define DATA 0x378
#define STATUS DATA+1
#define CONTROL DATA+2
void initprn();

char msg[50];
void pmsg();

void main()
{
	initprn();
	outportb(CONTROL,0xA0);
	scanf("%s",msg);
	pmsg();
	outportb(DATA,'\vt');
	outportb(CONTROL,0xFF);
}

void initprn()
{
	outportb(CONTROL,0xC); /*Reset Printer*/
	outportb(CONTROL,0x7); /*Draw Paper*/
}

void pmsg()
{
	int i;
	char a;
	int b;
	for(i=0;i<50;i++)
	{
		a=msg[i];
		b=toascii(a);
		outportb(CONTROL,0xA0);
		outportb(DATA,b);
		delay(100);
	}
	outportb(DATA,'\vt');
}