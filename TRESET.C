#include <stdio.h>
#include <time.h>

void setup();
void reset();

void main()
{
	clock_t t;
	int a,b;
	a=10;
	setup();
	while((a > 0) && (inportb(0x60) != 1))
	{
		t = clock();
		b = t / 18.2;
		a = 15-b;
		gotoxy(1,4);
		printf("\t\tThe system will restart in %.2d seconds\n\t\t\tEscape to restart now",a);
		gotoxy((4*b)+2,2);
		printf("%c%c%c%c",178,178,178,178);
	}
	reset();
}

void setup()
{
	int x;
	clrscr();
	/*Corners*/
	gotoxy(1,1);
	printf("%c",218);
	gotoxy(66,1);
	printf("%c",191);
	gotoxy(1,3);
	printf("%c",192);
	gotoxy(66,3);
	printf("%c",217);

	/*Vertical Bars*/
	gotoxy(1,2);
	printf("%c",179);
	gotoxy(66,2);
	printf("%c",179);

	/*Horizontal Bars*/
	for(x=2;x<66;x++)
	{
		gotoxy(x,1);
		printf("%c",196);
		gotoxy(x,3);
		printf("%c",196);
	}
}

void reset()
{
	outportb(0x64, 0xFE);
}