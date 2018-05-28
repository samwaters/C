#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>

void far mouse_handler();
void pp(int x, int y, int b);
void getarea(int ct);
int isrange(int x, int y);
void drawcolours();
void docolours();
void setcolours(int x, int y, int b);
void drawmouse(int x, int y, int b);
void savescr(int x, int y);
void putscr(int x, int y);
void nw();
void opn();
void sve();
char getpcolor(int clr);
int getccolor(char clr);

int ox, oy,ocx,ocy;
unsigned int pxcl;
int fillclr=WHITE;
int tool = 1;
int modflag = 0;
int pts[20000],pia;
int m[20][20];

void main()
{
	struct SREGS sregs;
	union REGS regs;
	int gm=DETECT, gd=VGAHI, ec;
	initgraph(&gm,&gd,"");
	ec=graphresult();
	if(ec != 0)
	{
		printf("Graphics Error: %s",grapherrormsg(ec));
		exit(-1);
	}
	regs.x.ax=0x0C;
	regs.x.dx=FP_OFF(mouse_handler);
	regs.x.cx=0xFF;
	sregs.es=FP_SEG(mouse_handler);
	pia=0;
	pxcl=0;
	int86x(0x33,&regs,&regs,&sregs);
	rectangle(0,20,639,430);
	drawcolours();
	setcolor(WHITE);
	ox=0;
	oy=0;
	while(inportb(0x60) != 1)
	{

	}
	exit(0);
}

void far mouse_handler()
{
	unsigned int x=_CX, y=_DX, b = _BX;
	drawmouse(x,y,b);
}

void drawmouse(int x, int y, int b)
{
	int i, j, k;
	int oldclr, oldfill;
	int pts[8];
	putscr(ocx, ocy);
	savescr(x,y);
	ocx=x;
	ocy=y;
	pts[0]=x;
	pts[1]=y;
	pts[2]=x;
	pts[3]=y+15;
	pts[4]=x+10;
	pts[5]=y+10;
	pts[6]=x;
	pts[7]=y;
	setfillstyle(SOLID_FILL, WHITE); /*Set fill colour*/
	fillpoly(4,pts); /*Draw mouse cursor*/
	oldclr = getcolor();
	oldfill = fillclr;
	setcolor(BLACK);
	/*Draw border round mouse*/
	line(x,y,x,y+15);
	line(x, y+15, x+10, y+10);
	line(x,y,x+10,y+10);
	setcolor(oldclr);
	setfillstyle(SOLID_FILL, oldfill);
	pp(x,y,b);
}

void savescr(int x, int y)
{
	int i, j, k;
	for(j=y;j<y+20;j++)
	{
		for(i=x;i<x+20;i++)
		{
			k = getpixel(i, j); /*Get pixel colour*/
			m[j-y][i-x] = k; /*Save it in an array*/
		}
	}
}

void putscr(int x, int y)
{
	int i, j, k;
	for(j=0;j<20;j++)
	{
		for(i=0;i<20;i++)
		{
			k=m[j][i]; /*Get pixel colour out of array*/
			putpixel(x+i, y+j, k); /*Draw it on screen*/
		}
	}
}

void pp(int x, int y, int b)
{
	if(tool == 1)
	{
		if(isrange(x,y) == 1)
		{
			if(b == 1)
			{
				line(ox,oy,x-1,y-1);
				modflag = 1;
			}
			ox=x-1;
			oy=y-1;
		}
	}
	if(tool > 1)
	{
		if(isrange(x,y) == 1)
		{
			if(b==1)
			{
				line(ox,oy,x-1,y-1);
				modflag=1;
				pts[pia]=x-1;
				pia++;
				pts[pia]=y-1;
				pia++;
			}
			if(b==0)
			{
				pts[pia]=pts[0];
				pia++;
				pts[pia]=pts[1];
				pia++;
				if(tool == 2)
					drawpoly(pia/2,pts);
				else
					fillpoly(pia/2,pts);
				getarea(pia);
				pia=0;
			}
			ox=x-1;
			oy=y-1;
		}
	}
	ocx=x;
	ocy=y;
	setcolours(x,y,b);
	docolours();
}

void getarea(int ct)
{
	int x1,y1,i,j;
	int x2,y2;
	int var1, var2, pc;
	float wc;
	wc=0;
	x1=10000;
	y1=10000;
	x2=0;
	y2=0;
	for(i=0;i<ct;i++)
	{
		j=i+1;
		if(pts[i] < x1)
			x1 = pts[i];
		if(pts[j] < y1)
			y1 = pts[j];
		if(pts[i] > x2)
			x2 = pts[i];
		if(pts[j] > y2)
			y2 = pts[j];
		i++;
	}
	for(var1=y1;var1<=y2;var1++)
	{
		for(var2=x1;var2<=x2;var2++)
		{
			pc=getpixel(var2, var1);
			if(pc == fillclr)
				wc++;
		}
	}
	gotoxy(1,1);
	if(wc > 1)
		printf("Area is %.0f pixels          ",wc);

}

int isrange(int x, int y)
{
	if((x > 2) && (x < 639) && (y > 22) && (y < 430))
		return 1;
	else
		return 0;
}

void drawcolours()
{
	int points[7];
	points[0] = 0;
	points[1] = 435;
	points[2] = 15;
	points[3] = 435;
	points[4] = 15;
	points[5] = 450;
	points[6] = 0;
	points[7] = 450;
	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);
	fillpoly(4,points);
	points[0] = 20;
	points[2] = 35;
	points[4] = 35;
	points[6] = 20;
	setcolor(YELLOW);
	setfillstyle(SOLID_FILL,YELLOW);
	fillpoly(4,points);
	points[0] = 40;
	points[2] = 55;
	points[4] = 55;
	points[6] = 40;
	setcolor(LIGHTGREEN);
	setfillstyle(SOLID_FILL,LIGHTGREEN);
	fillpoly(4,points);
	points[0] = 60;
	points[2] = 75;
	points[4] = 75;
	points[6] = 60;
	setcolor(GREEN);
	setfillstyle(SOLID_FILL,GREEN);
	fillpoly(4,points);
	points[0] = 80;
	points[2] = 95;
	points[4] = 95;
	points[6] = 80;
	setcolor(LIGHTBLUE);
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	fillpoly(4,points);
	points[0] = 100;
	points[2] = 115;
	points[4] = 115;
	points[6] = 100;
	setcolor(BLUE);
	setfillstyle(SOLID_FILL,BLUE);
	fillpoly(4,points);
	points[0] = 120;
	points[2] = 135;
	points[4] = 135;
	points[6] = 120;
	setcolor(MAGENTA);
	setfillstyle(SOLID_FILL,MAGENTA);
	fillpoly(4,points);
	points[0] = 140;
	points[2] = 155;
	points[4] = 155;
	points[6] = 140;
	setcolor(BROWN);
	setfillstyle(SOLID_FILL,BROWN);
	fillpoly(4,points);
	points[0] = 160;
	points[2] = 175;
	points[4] = 175;
	points[6] = 160;
	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL,BLACK);
	fillpoly(4,points);
	points[0] = 180;
	points[2] = 195;
	points[4] = 195;
	points[6] = 180;
	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	fillpoly(4,points);
	setcolor(WHITE);
	rectangle(300,435,330,465);
	line(305,460,325,440);
	rectangle(340,435,370,465); /*Empty Polygon*/
	rectangle(345,440,365,460);
	rectangle(380,435,410,465);
	points[0] = 385;
	points[1] = 440;
	points[2] = 405;
	points[3] = 440;
	points[4] = 405;
	points[5] = 460;
	points[6] = 385;
	points[7] = 460;
	fillpoly(4,points);
	/*New, Open and Save*/
	rectangle(460,435,500,452);
	outtextxy(470,440,"New");
	rectangle(510,435,550,452);
	outtextxy(515,440,"Open");
	rectangle(560,435,600,452);
	outtextxy(565,440,"Save");
}

void docolours()
{
	int dclr;
	int p[7];
	/*First do the forecolor selected*/
	p[0]=0;
	p[1]=460;
	p[2]=15;
	p[3]=460;
	p[4]=15;
	p[5]=475;
	p[6]=0;
	p[7]=475;
	setfillstyle(SOLID_FILL, getcolor());
	fillpoly(4,p);
	setfillstyle(SOLID_FILL, fillclr);

	/*Now the fillcolour*/
	p[0] = 20;
	p[2] = 35;
	p[4] = 35;
	p[6] = 20;
	dclr = getcolor();
	setcolor(fillclr);
	fillpoly(4, p);
	setcolor(dclr);
}

void setcolours(int x, int y, int b)
{
	if(b == 1)
	{
		if((y >=435) && (y <=450))
		{
			if((x >=0) && (x <= 15))
				setcolor(RED);
			if((x >=20) && (x <= 35))
				setcolor(YELLOW);
			if((x >=40) && (x <= 55))
				setcolor(LIGHTGREEN);
			if((x >=60) && (x <= 75))
				setcolor(GREEN);
			if((x >=80) && (x <= 95))
				setcolor(LIGHTBLUE);
			if((x >=100) && (x <= 115))
				setcolor(BLUE);
			if((x >=120) && (x <= 135))
				setcolor(MAGENTA);
			if((x >=140) && (x <= 155))
				setcolor(BROWN);
			if((x >=160) && (x <= 175))
				setcolor(BLACK);
			if((x >=180) && (x <= 195))
				setcolor(WHITE);

			/*Now do the tools thing*/
			if((x >= 300) && (x <= 330))
				tool = 1;
			if((x >= 340) && (x <= 370))
				tool = 2;
			if((x >= 380) && (x <= 410))
				tool = 3;


			/*Now do new, open, save*/
			if((x >=460) && (x <= 500))
				nw();
			if((x >=510) && (x <= 550))
				opn();
			if((x >=560) && (x <= 600))
				sve();
		}
	}
	if(b == 2)
	{
		if((y >=435) && (y <=450))
		{
			if((x >=0) && (x <= 15))
			{
				setfillstyle(SOLID_FILL,RED);
				fillclr = RED;
			}
			if((x >=20) && (x <= 35))
			{
				setfillstyle(SOLID_FILL,YELLOW);
				fillclr = YELLOW;
			}
			if((x >=40) && (x <= 55))
			{
				setfillstyle(SOLID_FILL,LIGHTGREEN);
				fillclr = LIGHTGREEN;
			}
			if((x >=60) && (x <= 75))
			{
				setfillstyle(SOLID_FILL,GREEN);
				fillclr = GREEN;
			}
			if((x >=80) && (x <= 95))
			{
				setfillstyle(SOLID_FILL,LIGHTBLUE);
				fillclr = LIGHTBLUE;
			}
			if((x >=100) && (x <= 115))
			{
				setfillstyle(SOLID_FILL,BLUE);
				fillclr = BLUE;
			}
			if((x >=120) && (x <= 135))
			{
				setfillstyle(SOLID_FILL,MAGENTA);
				fillclr = MAGENTA;
			}
			if((x >=140) && (x <= 155))
			{
				setfillstyle(SOLID_FILL,BROWN);
				fillclr = BROWN;
			}
			if((x >=160) && (x <= 175))
			{
				setfillstyle(SOLID_FILL,BLACK);
				fillclr = BLACK;
			}
			if((x >=180) && (x <= 195))
			{
				setfillstyle(SOLID_FILL,WHITE);
				fillclr = WHITE;
			}
		}
	}
}

void nw()
{
	char a;
	int points[9];
	if(modflag==1)
	{
		stt:
		gotoxy(1,1);
		printf("WARNING! Document is not saved! Save now (Y/N)?");
		scanf("%c",&a);
		if(a == 'y')
			sve();
		if(a == 'Y')
			sve();
		if((a != 'y') && (a != 'Y') && (a != 'n') && (a != 'N'))
		{
			printf("\a");
			goto stt;
		}
	}
	setfillstyle(SOLID_FILL,BLACK);
	setcolor(WHITE);
	points[0] = 0;
	points[1] = 20;
	points[2] = 639;
	points[3] = 20;
	points[4] = 639;
	points[5] = 430;
	points[6] = 0;
	points[7] = 430;
	points[8] = 0;
	points[9] = 20;
	fillpoly(4,points);
	tool=1;
	modflag=0;
	gotoxy(1,1);
	printf("\t\t\t\t\t\t\t");
}

void opn()
{
	FILE *fh;
	int x, y, p;
	char c;
	char fname[30];
	gotoxy(1,1);
	printf("\t\t\t\t\t\t\t\t");
	gotoxy(1,1);
	printf("File name and path:");
	scanf("%s",fname);
	fh=NULL;
	fh=fopen(fname,"r");
	c=0;
	for(y=21;y<430;y++)
	{
		for(x=1;x<639;x++)
		{
			c=fgetc(fh);
			p=getccolor(c);
			putpixel(x,y,p);
		}
	}
	fclose(fh);
	fh = NULL;
	gotoxy(1,1);
	printf("\t\t\t\t\t\t\t\t");
}

void sve()
{
	FILE *fh;
	int x, y, p;
	char fname[30], c;
	gotoxy(1,1);
	printf("\t\t\t\t\t\t\t\t");
	gotoxy(1,1);
	printf("File name and path:");
	scanf("%s",fname);
	fh=NULL;
	fh=fopen(fname,"a+");
	for(y=21;y<430;y++)
	{
		for(x=1;x<639;x++)
		{
			p=getpixel(x,y);
			c=getpcolor(p);
			fprintf(fh,"%c",c);
		}
	}
	fclose(fh);
	fh=NULL;
	gotoxy(1,1);
	printf("\t\t\t\t\t\t\t\t");
}

char getpcolor(int clr)
{
	switch(clr)
	{
	case 0:
		return 'A';
	case 1:
		return 'B';
	case 2:
		return 'C';
	case 3:
		return 'D';
	case 4:
		return 'E';
	case 5:
		return 'F';
	case 6:
		return 'G';
	case 7:
		return 'H';
	case 8:
		return 'I';
	case 9:
		return 'J';
	case 10:
		return 'K';
	case 11:
		return 'L';
	case 12:
		return 'M';
	case 13:
		return 'N';
	case 14:
		return 'O';
	case 15:
		return 'P';
	}
}

int getccolor(char clr)
{
	switch(clr)
	{
	case 'A':
		return 0;
	case 'B':
		return 1;
	case 'C':
		return 2;
	case 'D':
		return 3;
	case 'E':
		return 4;
	case 'F':
		return 5;
	case 'G':
		return 6;
	case 'H':
		return 7;
	case 'I':
		return 8;
	case 'J':
		return 9;
	case 'K':
		return 10;
	case 'L':
		return 11;
	case 'M':
		return 12;
	case 'N':
		return 13;
	case 'O':
		return 14;
	case 'P':
		return 15;
	}
}

