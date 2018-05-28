#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <graphics.h>

char pwd[30];
char amsg[30];
float x=480, y=200;
int mp=0;

void timerproc();
void timer(int interval);
void enterpass();

void main(int argc, char *argv[])
{
	int gd=DETECT, gm=IBM8514HI;
	if(argc < 3)
	{
		printf("Usage: lockdown.exe <password> <away message>\n");
		exit(-1);
	}
	strcpy(pwd,argv[1]);
	strcpy(amsg,argv[2]);
	clrscr();
	initgraph(&gd,&gm,"");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
	timer(100);

}

void timer(int ival)
{
	clock_t ck;
	float a,b;
	b=0;
	tlock:
	ck=clock();
	a=(ck/CLK_TCK);
	if(((a - b) * 1000) >= ival)
	{
		timerproc();
			b=a;
	}
	if(inportb(0x60) == 1)
		enterpass();
	else
		goto tlock;
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
	setcolor(WHITE);
	outtextxy(x,y,amsg);
	if(mp==0)
		x=x-10;
	else
		x=x+10;
	if(x<=0)
		mp=1;
	if(x>640)
		mp=0;
}

void enterpass()
{
	char upass[30];
	int z;
	int gd=DETECT, gm=IBM8514HI;
	restorecrtmode();
	clrscr();
	gotoxy(1,1);
	printf("System is locked.\nEnter unlock password:");
	scanf("%s",upass);
	z=strcmp(upass,pwd);
	if(z==0)
	{
		clrscr();
		exit(0);
	}
	else
	{
		clrscr();
		initgraph(&gd,&gm,"");
		settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
		timer(100);
	}
}