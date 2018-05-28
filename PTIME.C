#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>

void timerproc();
void timer(int interval);
void doexit();
void helpmsg();
void aboutmsg(char *p2p);
void interesting();
int gv,bp;

void main(int argc, char *argv[])
{
	char x[10]; /*Command line argument*/
	char y[10] = "beep\0"; /*Comparison string*/
	char a[10] = "help\0"; /*Another comparison string*/
	char b[10] = "about\0"; /*And another*/
	char c[10] = "/?\0"; /*And yet another*/
	char d[10] = "BITE_ME!"; /*Don't ask!*/
	int z;
	strcpy(x,argv[1]); /*Copy command line argument 1 to x*/
	z=strcmp(x,a); /*Compare it with the first comparison string*/
	if(z==0) /*If equal*/
		helpmsg(); /*Call a function*/
	z=strcmp(x,b);
	if(z==0)
		aboutmsg(argv[0]);
	z=strcmp(x,c);
	if(z==0)
		helpmsg();
	z=strcmp(x,d);
	if(z==0)
		interesting();
	z=strcmp(x,y);
	if(z==0)
		bp=1;
	else
		bp=0; /*Disable beeping*/
	timer(1000);
}

void timer(int interval) /*Interval in ms*/
{
	clock_t ck; /*Clock ticks since program start*/
	float a,b;  /*a = Seconds since program start, b = Seconds Temp*/
	int c,ext; /*c = variable to keep timer going, ext = do we exit*/
	b = 0;
	c = 1;
	while(c > 0)
	{
		ck = clock();
		a = (ck / CLK_TCK);
		if(((a - b) * 1000) >= interval)
		{
			timerproc(); /*The proc to call every cycle*/
			b = a;
		}
		doexit();
	}

}

void timerproc()
{
	struct tm * now;
	time_t rawtime;
	gv++;
	rawtime = time(NULL);
	now = localtime(&rawtime);
	printf("\b\b\b\b\b\b\b\b");
	printf("%.2d:%.2d:%.2d",now->tm_hour, now->tm_min, now->tm_sec);
	if(bp==1) /*If beeps enabled*/
		printf("\a"); /*Beep*/
}

void doexit()
{
	int a;
	a = inportb(0x60);
	if(a < 100)
	{
		if(gv >= 10)
		{
			printf("\n");
			exit(0);
		}
	}
}

void helpmsg()
{
	printf("\nCommand line options:\n");
	printf("ptime.exe will run the program until Escape is pressed.\n");
	printf("ptime.exe beep will run the program until Escape is pressed, but will beep\nevery second also.\n");
	printf("ptime.exe help displays this message.\n");
	printf("ptime.exe /? also displays this message.\n");
	printf("ptime.exe about displays program information.\n");
	printf("To exit ptime.exe, press the Escape key.\n");
	exit(0);
}

void aboutmsg(char *p2p)
{
	printf("\nAbout ptime.exe\n");
	printf("Program path: %s\n",p2p);
	printf("ptime.exe is a simple program that displays the time every second.\n");
	printf("It uses the computer's clock and a hard-coded timer to calculate when a second\nhas elapsed, and then gets the time from BIOS.\n");
	printf("It is written in Borland's Turbo C version 2.01\n");
	printf("Coded by Sam Waters (Jul 2003)\n");
	printf("Program version 1.0.0\n");
	printf("Program date 18/7/2003\n");
	printf("For more programs and code listings, visit www.samwaters.com\n");
	exit(0);
}

void interesting()
{
	int x;
	printf("\nWelcome to the secret part of the program!\n");
	printf("This is what programmers do when they get bored I guess...\n");
	printf("Anyway, thanks for using ptime =)\n");
	printf("Press escape when you've finished listening to the pretty sounds.\n");
	while(inportb(0x60) != 1)
	{
		x=random(10000);
		sound(x);
		delay(100);
	}
	nosound();
	exit(0);
}
