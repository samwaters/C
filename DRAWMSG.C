#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>

void getmsg();
void drawchar(char chr, int attr, int row, int col);
void drawborder();
void writemsg();
void aniborder();

char msg[300];
int border, msglen, bfcolor, bcolor;

void main()
{
	union REGS regs;
	int col, row, chr, attr;
	time_t tt1;
	struct tm *tt2;
	tt1 = time(NULL);
	tt2 = localtime(&tt1);
	getmsg();
	srand(tt2->tm_sec);
	drawborder();
	writemsg();
	while(inportb(0x60) != 1)
	{
		aniborder();
		writemsg();
	}
}

void getmsg()
{
	int a;
	char b;
	b=0;
	a=0;
	printf("Enter message:");
	while(b != 13)
	{
		b = getche();
		if(b != 8)
		{
			msg[a] = b;
			a++;
		}
		else
		{
			a--;
		}
	}
	msglen = a - 1;
	msg[a] = '\0';
	a++;
	printf("\nEnter border ASCII code:");
	scanf("%d",&border);
	printf("Enter border colour:");
	scanf("%d",&bcolor);
	printf("Enter border flash colour:");
	scanf("%d",&bfcolor);
}

void drawborder()
{
	union REGS regs;
	int row,col;
	regs.h.ah=0;
	regs.h.al = 1;
	int86(0x10,&regs,&regs);
	row = 0;
	nl:
	for(col=0;col<(msglen+4);col++)
	{
		drawchar(border,bcolor,col,row);
	}
	if(row == 0)
	{
		row = 4;
		goto nl;
	}
	drawchar(border,bcolor,0,1);
	drawchar(border,bcolor,msglen+3,1);
	drawchar(border,bcolor,0,2);
	drawchar(border,bcolor,msglen+3,2);
	drawchar(border,bcolor,0,3);
	drawchar(border,bcolor,msglen+3,3);
}

void drawchar(char chr, int attr, int col, int row)
{
	union REGS regs;

	regs.h.ah = 0x01;
	regs.h.ch = row;
	regs.h.cl = row;
	regs.x.cx = 0x00;
	int86(0x10,&regs,&regs);

	regs.h.ah = 0x02;
	regs.h.dh = row;
	regs.h.dl = col;
	regs.h.bh = 0;
	int86(0x10,&regs,&regs);
	regs.h.ah = 0x09;
	regs.h.bh = 0;
	regs.x.cx = 1;
	regs.h.al = chr;
	regs.h.bl = attr;
	int86(0x10,&regs,&regs);
}

void writemsg()
{
	int row, col;
	row = 2;
	for(col = 2;col <= (msglen+1);col++)
	{
		drawchar(msg[col-2],random(10) + 1,col,row);
	}
}

void aniborder()
{
	int i;
	if(inportb(0x60) == 1)
		exit(0);
	for(i=0;i<msglen+4;i++)
	{
		drawchar(border,bfcolor,i,0);
		if(i > 0)
			drawchar(border,bcolor,i-1,0);
		delay(500);
	}
	for(i=0;i<5;i++)
	{
		drawchar(border,bfcolor,msglen+3,i);
		if(i > 0)
			drawchar(border,bcolor,msglen+3,i-1);
		delay(500);
	}
	for(i=msglen+2;i>=0;i--)
	{
		drawchar(border,bfcolor,i,4);
		if(i >= 0)
			drawchar(border,bcolor,i+1,4);
		delay(500);
	}
	for(i=3;i>=0;i--)
	{
		drawchar(border,bfcolor,0,i);
		if(i >= 0)
			drawchar(border,bcolor,0,i+1);
		delay(500);
	}
}