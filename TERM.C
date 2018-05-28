#include <stdio.h>
#include <conio.h>

#define PORT 0x3F8

void main()
{
	int a;
	while(inportb(0x60) != 1)
	{
		a = inportb(PORT);
		if(a < 225)
		{
			printf("%c",a);
		}
		if(kbhit() != 0)
		{
			a = getch();
			outportb(PORT,a);
			outportb(PORT,250);
		}
	}
}