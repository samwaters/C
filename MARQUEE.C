#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>

char mstring[30];
float x=480, y=200;
int mp=0;
int tcolor;

void timerproc();
void timer(int interval);

void main()
{
	int ival,tsize,i;
	char x;
	int gd=DETECT, gm=IBM8514HI;
	clrscr();
	gotoxy(1,1);
	printf("Enter marquee message (30 chars max):");
	/*scanf("%s",mstring);*/
	i=0;
	gnc:
	x=getche();
	if(x != 13)
	{
		mstring[i]=x;
		i++;
		goto gnc;
	}
	gotoxy(1,2);
	printf("Enter scroll speed (1=fastest, 10000=slowest):");
	scanf("%d",&ival);
	printf("Enter font size (1 - 10):");
	scanf("%d",&tsize);
	printf("Enter text colour (1 - 15):");
	scanf("%d",&tcolor);
	initgraph(&gd,&gm,"");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,tsize);
	timer(ival);
}

void timer(int ival)
{
	clock_t ck;
	float a,b;
	b=0;
	while(inportb(0x60) != 1)
	{
		ck=clock();
		a=(ck/CLK_TCK);
		if(((a - b) * 1000) >= ival)
		{
			timerproc();
			b=a;
		}
	}
}

void timerproc()
{
	int poly[9];
	setfillstyle(SOLID_FILL,BLACK);
	setcolor(BLACK);
	poly[0]=x-10;
	poly[1]=y;
	poly[2]=x+1000;
	poly[3]=y;
	poly[4]=x+1000;
	poly[5]=y+300;
	poly[6]=x-10;
	poly[7]=y+300;
	poly[8]=x-10;
	poly[y]=y;
	fillpoly(4,poly);
	setcolor(tcolor);
	outtextxy(x,y,mstring);
	if(mp==0)
		x=x-10;
	else
		x=x+10;
	if(x<=0)
		mp=1;
	if(x>640)
	{
		mp=0;
		/*y=random(400);*/
	}
}