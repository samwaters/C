/*Sam's Keypress --> COM1 Routine*/
/*Gets character pressed on keyboard and sends to COM1*/
/*Press ESC to exit*/

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#define PORT 0x3F8

void main(void)
{
	char a,c;
	int b;
	bob:
	while( !kbhit() )
	{
	      b++;
	}
	a=getch();
	printf("%c",a);
	c=(unsigned char)toascii(a);
	outportb(PORT,b);
	if(a==27)
		exit(0);
	goto bob;
}
