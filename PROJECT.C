#include <stdio.h>
#include <graphics.h>
#include <math.h>

float angle, vel;
int ox=0;
int oy=235;
float tint=0.1;
void drawaxis();
void drawgraph();

void main()
{
	clrscr();
	gotoxy(1,1);
	printf("Enter projection angle (0 - 90):");
	scanf("%f",&angle);
	if(angle < 0)
	{
		printf("\aPlease enter a valid argument\n");
		exit(-1);
	}
	if(angle > 90)
	{
		printf("\aPlease enter a valid argument\n");
		exit(-1);
	}
	printf("Enter projection velocity:");
	scanf("%f",&vel);
	if(vel < 0)
	{
		printf("\aPlease enter a valid argument\n");
		exit(-1);
	}
	drawaxis();
	drawgraph();
}

void drawaxis()
{
	int gd=DETECT, gm=IBM8514HI;
	initgraph(&gd,&gm,"");
	cleardevice();
	line(0,0,0,480);
	line(0,235,640,235);
}

void drawgraph()
{
	/*x cos angle t		x sin angle t - 4.9t^2*/
	float t=0;
	float y;
	while(y <= 235)
	{
		y=235-((vel*sin(angle)*t)-(4.9*(t*t)));
		line(ox,oy,t,y);
		ox=t;
		oy=y;
		t=t+tint;
	}
}