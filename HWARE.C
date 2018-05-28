#include <stdio.h>
#include <conio.h>

void lighton(int light);

void main()
{
	clrscr();
	gotoxy(1,1);
	printf("Press 1 to turn on light 1\nPress 2 to turn on light 2\nPress 3 to turn both lights on\nPress 4 to turn the Fan on\nPress 5 to turn All objects on\nPress TAB to turn off the objects\nNO OBJECTS ON  ");
	while(inportb(0x60) != 1)
	{
		if(inportb(0x60) == 2)
			lighton(1);
		if(inportb(0x60) == 3)
			lighton(2);
		if(inportb(0x60) == 4)
			lighton(3);
		if(inportb(0x60) == 5)
			lighton(4);
		if(inportb(0x60) == 6)
			lighton(5);
	}
}

void lighton(int light)
{
	if(light==1)
	{
		while(inportb(0x60) != 15)
		{
			outportb(0x378,0x01);
			gotoxy(1,7);
			printf("LIGHT 1 ON   ");
		}
		outportb(0x378,0x00);
		gotoxy(1,7);
		printf("NO OBJECTS ON  ");
	}
	if(light==2)
	{
		while(inportb(0x60) != 15)
		{
			outportb(0x378,0x02);
			gotoxy(1,7);
			printf("LIGHT 2 ON   ");
		}
		outportb(0x378,0x00);
		gotoxy(1,7);
		printf("NO OBJECTS ON  ");
	}
	if(light==3)
	{
		while(inportb(0x60) != 15)
		{
			outportb(0x378,0x03);
			gotoxy(1,7);
			printf("BOTH LIGHTS ON");
		}
		outportb(0x378,0x00);
		gotoxy(1,7);
		printf("NO OBJECTS ON  ");
	}
	if(light==4)
	{
		while(inportb(0x60) != 15)
		{
			outportb(0x378,0x04);
			gotoxy(1,7);
			printf("FAN ON         ");
		}
		outportb(0x378,0x00);
		gotoxy(1,7);
		printf("NO OBJECTS ON  ");
	}
	if(light==5)
	{
		while(inportb(0x60) != 15)
		{
			outportb(0x378, 0x07);
			gotoxy(1,7);
			printf("ALL OBJECTS ON  ");
		}
		outportb(0x378,0x00);
		gotoxy(1,7);
		printf("NO OBJECTS ON  ");
	}
}
