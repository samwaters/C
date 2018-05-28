#include <stdio.h>
#include <stdlib.h>

void main()
{
	int i;
	srand(234);
	outportb(0x60, 0xED);
	outportb(0x60, 0x00);
	while(inportb(0x60) != 1)
	{
		i = random(8);
		outportb(0x60, 0xED);
		outportb(0x60, i);
		delay(10000);
	}
}