#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define PROMPT "C:\\>"
#define DOSMSG "Mircosoft Windwos 2003 [Version 6.66.3333]"
#define DOSMSG2 "(C) Copyright 1985-2003 Mircosoft Crap."

void main()
{
	char msg1[20] = "Busy.", msg2[20] = "Go Away.", msg3[20] = "Piss Off.";
	char msg4[20] = "Shut Up.", msg5[20] = "No.", msg6[20] = "Don't Feel Like It.";
	char msg7[20] = "Fuck You.", msg8[50] = "I ALWAYS do thins for YOU. Do something for ME.";
	char msg9[20] = "I Feel SO Used.", msg10[30] = "Go Look up Porn or Something.";
	char tmp;
	int a;
	clrscr();
	gotoxy(1,1);
	printf("%s\n%s\n\n",DOSMSG,DOSMSG2);
	srand(52);
	strt:
	a=random(10) + 1;
	printf("%s",PROMPT);
	scanf("%s",tmp);
	switch(a)
	{
	case 1:
		printf("%s\n\n",msg1);
		break;
	case 2:
		printf("%s\n\n",msg2);
		break;
	case 3:
		printf("%s\n\n",msg3);
		break;
	case 4:
		printf("%s\n\n",msg4);
		break;
	case 5:
		printf("%s\n\n",msg5);
		break;
	case 6:
		printf("%s\n\n",msg6);
		break;
	case 7:
		printf("%s\n\n",msg7);
		break;
	case 8:
		printf("%s\n\n",msg8);
		break;
	case 9:
		printf("%s\n\n",msg9);
		break;
	case 10:
		printf("%s\n\n",msg10);
		break;
	}
	goto strt;
}