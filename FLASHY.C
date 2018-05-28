#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <time.h>

void drawchar(char chr, int attr, int row, int col);
void help();
void about();

void main(int argc, char *argv[])
{
	union REGS regs;
	FILE *fh;
	int cl, rw, lt, att;
	int cnt=0,z,mde,ac,nc=0,tmp,i,clear_at;
	char x[10]; /*User Args*/
	char arg;
	time_t t1;
	struct tm *t2;
	t1 = time(NULL);
	t2 = localtime(&t1);
	srand(t2->tm_sec);
	mde = -1;
	for(i=1;i<argc;i++)
	{
		z = strcmp(argv[i],"-m");
		if(z == 0)
		{
			tmp = strcmp(argv[i+1],"let");
			if(tmp == 0)
				mde = 1;
			tmp = strcmp(argv[i+1],"face");
			if(tmp == 0)
				mde = 2;
			tmp = strcmp(argv[i+1],"random");
			if(tmp == 0)
				mde = 3;
			tmp = strcmp(argv[i+1],"custom");
			if(tmp == 0)
				mde = 4;
		}
		z = strcmp(argv[i],"-c");
		if(z == 0)
		{
			tmp = atoi(argv[i+1]);
			if(tmp > 0)
				clear_at = tmp;
			if(tmp < 1)
				clear_at = 200;
		}
		z = strcmp(argv[i],"-nc");
		if(z == 0)
		{
			nc = 1;
		}
		z = strcmp(argv[i],"-r");
		if(z == 0)
		{
			tmp = atoi(argv[i+1]);
			if(tmp > 0)
				srand(tmp);
		}
		z = strcmp(argv[i],"-h");
		if(z == 0)
		{
			help();
			exit(0);
		}
		z = strcmp(argv[i],"/?");
		if(z == 0)
		{
			help();
			exit(0);
		}
		z = strcmp(argv[i],"-a");
		if(z == 0)
		{
			about();
			exit(0);
		}
	}
	if(mde == -1)
		mde = 2;
	if(mde == 4)
	{
		printf("Ascii Code:");
		scanf("%d",&ac);
	}
	clrscr();
	fh=fopen("c:/run.txt","a+");
	if(fh == NULL)
	{
		printf("Disk IO Error\n");
		exit(0);
	}
	regs.h.ah=0;
	regs.h.al = 1;
	int86(0x10,&regs,&regs);
	while(inportb(0x60) != 1)
	{
		/*clrscr();*/
		cl=random(41);
		rw = random(26);
		if(mde == 1)
			lt = random(26) + 65;
		if(mde == 2)
			lt = 0x02;
		if(mde == 3)
			lt = random(87) + 30;
		if(mde == 4)
			lt = ac;
		att = random(9);
		drawchar(lt, att, cl, rw);
		cnt++;
		if((cnt == clear_at) && (nc == 0))
		{
			clrscr();
			cnt=0;
		}
		delay(150);
	}
	fcloseall();
	unlink("c:/run.txt");
	regs.h.ah = 0;
	regs.h.al = 2;
	int86(0x10,&regs,&regs);
}

void drawchar(char chr, int attr, int col, int row)
{
	union REGS regs;
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

void about()
{
	printf("\n--%c About Flashy %c--\n",0x02,0x02);
	printf("Flashy.exe is a simple program demonstrating BIOS routines and command line parameters.\n");
	printf("It draws characters on the screen at random locations and in random colours.\n");
	printf("It was written by Sam Waters in Borland's Turbo C 2.03\n");
	printf("Compiled at 12:14am on 24th July 2004\n");
	printf("To exit Flashy, press Escape\n");
}

void help()
{
	printf("Flashy.exe -m [mode] -c [clear] -nc -r [random] -h /? -a\n");
	printf("-m [mode] sets no. of characters displayed on screen where [mode] is let, face, random or custom.\nIf -m is omitted or [mode] is invalid then face is assumed.\n");
	printf("-c [clear] sets no. of characters displayed before the screen is cleared where [clear] is a number.\nIf -c is omitted or [clear] is invalid then 200 is assumed.\n");
	printf("-nc instructs Flashy not to clear the screen at all\n");
	printf("-r [random] sets the seed for the random number generator used in Flashy where [random] is the seed.\nIf -r is omitted or [random] is invalid then the second is used.\n");
	printf("-h and /? display this message\n");
	printf("-a displays the about Flashy message\n");
}