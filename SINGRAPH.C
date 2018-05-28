#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define PI 3.14159 /*PI as C does not have a constant*/
#define TDELAY 50
void drawaxis();
void drawsine();
void drawcos();
void drawtan();
void drawsq();
void sawtooth();
void rndom();
void clearit();
int hilo=1;

void main()
{
	int gdriver=DETECT, gmode=IBM8514HI, ec; /*Autodetect Graphics, 1024*768*256*/
	int pr=0;
	/*Initialise Graphics Driver*/
	initgraph(&gdriver, &gmode,"");
	/*Any error will be here*/
	ec = graphresult();
	if(ec != 0)
	{
		/*There has been an error*/
		printf("GRAPHICS ERROR: %s",grapherrormsg(ec));
		exit(-1);
	}
	drawaxis(); /*Set axis*/
	outtextxy(25,450,"1.Sine 2.Cosine 3.Tangent 4.Square 5.Sawtooth 6.Random 7.Clear Esc.Exit");
	while(pr != 1)
	{
		pr = inportb(0x60);
		if(pr < 100)
		{
			switch(pr)
			{
			case 2:
				drawsine();
				break;
			case 3:
				drawcos();
				break;
			case 4:
				drawtan();
				break;
			case 5:
				drawsq();
				break;
			case 6:
				sawtooth();
				break;
			case 7:
				rndom();
				break;
			case 8:
				clearit();
				break;
			default:
				break;
			}
		}
	}
}

void drawsine()
{
	int x,x1;
	float y, ox, oy;
	ox = 20;  /*Start*/
	oy = 235; /*Coordinates*/
	setcolor(4);
	for(x=20;x<651;x++)
	{
		/*Calculate the sine of the point x*/
		x1 = x - 20;
		y = 235 - (sin(x1 * PI / 180) * 100);
		/*Draw line from previous point to this*/
		line(ox,oy,x,y);
		/*Set previous points*/
		ox = x;
		oy = y;
		/*Wait a bit*/
		delay(TDELAY);
	}
	/*Write graph label and reset for Cos*/
	outtextxy(80,119,"y = sin(x)");
}

void drawcos()
{
	int x, x1;
	float y, ox, oy;
	ox = 20;
	oy = 235;
	setcolor(3);
	for(x=20;x<651;x++)
	{
		/*Do the same as above but for Cosine*/
		x1 = x - 20;
		y = 235 - (cos(x1 * PI / 180) * 100);
		line(ox,oy,x,y);
		ox = x;
		oy = y;
		delay(TDELAY);
	}
	outtextxy(160,349,"y = cos(x)");
}

void drawtan()
{
	int x1;
	float x,y, ox, oy,tp1, tp2;
	ox = 20;
	oy = 235;
	x = 20;
	tp1 = -1000; /*Min Y*/
	tp2 = 1000;  /*Max Y*/
	setcolor(2);
	for(x=20;x<651;x++)
	{
		/*Same as above but for Tan*/
		x1 = x - 20;
		y = 235 - (tan(x1 * PI / 180) * 100);
		if((y > tp1) && (y < tp2)) /*Stop vertical lines from top to bottom*/
		{
			line(ox,oy,x,y);
			delay(TDELAY);
		}
		ox = x;
		oy = y;
	}
	outtextxy(450,100,"y = tan(x)");
}

void drawsq()
{
	int tvar,x,y,ox,oy;
	ox=20;
	oy=135;
	tvar=0;
	for(x=20;x<651;x++)
	{
		setcolor(5);
		if(hilo == 1)
			y=135;
		else
			y=335;
		line(ox,oy,x,y);
		delay(TDELAY);
		tvar++;
		if(tvar == 90)
		{
			if(hilo==1)
			{
				hilo=0;
				tvar=0;
			}
			else
			{
				hilo=1;
				tvar=0;
			}
		}
		ox=x;
		oy=y;
	}
}

void sawtooth()
{
	int x, ox, oy,pos;
	ox=20;
	oy=235;
	pos=235;
	setcolor(9);
	for(x=20;x<651;x++)
	{
		if(pos > 135)
		{
			line(ox,oy,x,pos);
			pos--;
			delay(TDELAY);
		}
		if(pos == 135)
		{
			pos=335;
			line(ox,oy,x,pos);
			delay(TDELAY);
		}
		ox=x;
		oy=pos;
	}
}

void rndom()
{
	int x, y,ox,oy;
	time_t t;
	struct tm *tt;
	ox=20;
	oy=235;
	t=time(NULL);
	tt=localtime(&t);
	setcolor(10);
	srand(tt->tm_sec);
	for(x=20;x<651;x++)
	{
		y=random(236) + 100;
		line(ox,oy,x,y);
		ox=x;
		oy=y;
		delay(TDELAY);
	}
}

void drawaxis()
{
	/*Draw and label axis*/
	line(20,0,20,500);
	line(20,235,1000,235);
	outtextxy(22,250,"0");
	outtextxy(102,250,"90");
	outtextxy(189,250,"180");
	outtextxy(279,250,"270");
	outtextxy(369,250,"360");
	outtextxy(459,250,"450");
	outtextxy(549,250,"540");
	outtextxy(639,250,"630");
	outtextxy(0,129,"+1");
	outtextxy(0,329,"-1");
	line(110,235,110,245);
	line(200,235,200,245);
	line(290,235,290,245);
	line(380,235,380,245);
	line(470,235,470,245);
	line(560,235,560,245);
	line(650,235,650,245);
	outtextxy(210,10,"Mathematical (and random) Graphs");
}

void clearit()
{
	cleardevice();
	setcolor(WHITE);
	drawaxis();
	outtextxy(25,450,"1.Sine 2.Cosine 3.Tangent 4.Square 5.Sawtooth 6.Random 7.Clear Esc.Exit");
}