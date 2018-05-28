#include <stdio.h>
#include <time.h>
#include <dos.h>
void disptme();
void stme();

void main()
{
	int a;
	printf("\n1. Display Time\n2. Set Time\n3. Exit\nMake a selection:");
	scanf("%d",&a);
	switch(a)
	{
	case 1:
		disptme();
		break;
	case 2:
		stme();
		break;
	case 3:
		exit(0);
		break;
	default:
		printf("\nInvalid Selection\n");
		main();
		break;
	}
}

void disptme()
{
	time_t rawtime;
	struct tm *tme;
	rawtime = time(NULL);
	tme = localtime(&rawtime);
	printf("The time is %d:%d:%d",tme->tm_hour, tme->tm_min, tme->tm_sec);
	main();
}
void stme()
{
	struct time *nt;
	int h,m,s;
	printf("Hour:");
	scanf("%d",&h);
	printf("Minute:");
	scanf("%d",&m);
	printf("Second:");
	scanf("%d",&s);
	nt->ti_hour = h;
	nt->ti_min = m;
	nt->ti_sec = s;
	settime(nt);
	printf("The time has been set to %d:%d:%d",h,m,s);
	main();
}