#include <stdio.h>

#define PORT 0x3F8

void waitforstart();

void main()
{
	FILE *fh;
	char x[30];
	printf("File to receive:");
	scanf("%s",x);
	waitforstart();
	printf("Ok let's go!");
}

void waitforstart()
{
	int x=0,y=0;
	char a;
	while(x != 0x251)
	{
		x = inportb(PORT);
		switch(y)
		{
		case 0: a='|'; break;
		case 1: a='/'; break;
		case 2: a='-'; break;
		case 3: a='\\'; break;
		}
		gotoxy(1,2);
		printf("Waiting %c",a);
		delay(100);
	}
	outportb(PORT,0x250);
}