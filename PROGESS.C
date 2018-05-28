#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>

struct pstruct
{
	int sx;
	int sy;
	int mx;
	int my;
};

void drawprog(struct pstruct *x, int prog);

void main()
{
	int gd=DETECT, gm=VGAHI,a;
	struct pstruct *x;
	x->sx=10;
	x->sy=10;
	x->mx=530;
	x->my=50;
	initgraph(&gd,&gm,"");
	for(a=100;a>-1;a--)
	{
		drawprog(x,a);
		delay(1000);
	}
}

void drawprog(struct pstruct *x, int prog)
{
	int tmp;
	int pat=SOLID_FILL,clr=WHITE;
	cleardevice();
	setfillstyle(pat,clr);
	tmp=((x->mx / 100) * prog) + (x->sx + 10);
	rectangle(x->sx,x->sy,x->mx, x->my);
	bar(x->sx + 10,x->sy + 10,tmp,x->my - 10);
}
