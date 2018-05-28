#include <stdio.h>
#include <dos.h>
#include <stdlib.h>

void far mh();
int attr=0x02;

void main()
{
	union REGS regs;
	struct SREGS sregs;
	srand(10);
	/*Set screen mode*/
	regs.h.ah=0;
	regs.h.al=1;
	int86(0x10,&regs,&regs);

	/*Set mouse handle*/
	regs.x.ax = 0x0C;
	regs.x.dx = FP_OFF(mh);
	regs.x.cx = 0xFF;
	sregs.es = FP_SEG(mh);
	int86x(0x33,&regs,&regs,&sregs);
	while(inportb(0x60) != 1)
	{
	}
}

void far mh()
{
	unsigned int x=_CX, y=_DX, b=_BX;
	union REGS regs;
	int atr;
	clrscr();
	/*Move to pos*/
	regs.h.ah=2;
	regs.h.dh=y;
	regs.h.dl=x;
	regs.h.bh=0;
	int86(0x10,&regs,&regs);

	/*Print char*/
	regs.h.ah=0x09;
	regs.h.bh=0;
	regs.x.cx=1;
	regs.h.al=0x02;
	regs.h.bl=attr;

	int86(0x10,&regs,&regs);
	if(b == 1)
	{
		atr=random(255);
		attr=atr;
	}
}