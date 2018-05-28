#include <stdio.h>
#include <graphics.h>

FILE *fh;
int BHEIGHT, BWIDTH;

int lookup(char let);
void drawit();

void main()
{
	char fname[30];
	printf("Enter path and filename to open:");
	scanf("%s",fname);
	printf("Enter bitmap HEIGHT:");
	scanf("%d",&BHEIGHT);
	printf("Enter bitmap WIDTH:");
	scanf("%d",&BWIDTH);
	fh=fopen(fname,"r+");
	if(fh==NULL)
	{
		printf("Failed to open input file\n");
		exit(-1);
	}
	drawit();
}

void drawit()
{
	int gd=DETECT, gm=IBM8514HI,ec;
	int x,y,z;
	char w;
	initgraph(&gd,&gm,"");
	ec=graphresult();
	if(ec != 0)
	{
		printf("Graphics System Error: %s",grapherrormsg(ec));
		exit(-1);
	}
	cleardevice();
	for(y=0;y<BHEIGHT;y++)
	{
		for(x=0;x<BWIDTH;x++)
		{
			w=fgetc(fh);
			z=lookup(w);
			putpixel(x,y,z);
		}
	}
}

int lookup(char let)
{
	switch(let)
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
}