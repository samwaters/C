#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

void main()
{
	int a,b;
	srand(678);
	while(inportb(0x60) != 1)
	{
		a=random(2000);
		sound(a);
		b = random(5650);
		delay(b);
	}
	nosound();
}