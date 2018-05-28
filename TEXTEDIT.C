#include <stdio.h>
#include <conio.h>

struct
{
	char chars[80];
}lines[600];

int cline, cchar, csline, cschar;
int lastchar=1;
void dointerface();
void lookup(int kc);
int caps=0;

void main()
{
	int chr;
	cline=1;
	cchar=1;
	csline=2;
	cschar=2;
	dointerface();
	while(inportb(0x60) != 1)
	{
		chr=inportb(0x60);
		if(chr < 100)
		{
			if(chr != lastchar)
			{
				lookup(chr);
			}
		}
		lastchar=chr;
	}
}

void dointerface()
{
	int i;
	clrscr();
	gotoxy(1,1);
	printf("Ý---------------------------------- Sam Edit ----------------------------------Ý");
	for(i=0;i<22;i++)
	{
		printf("Ý                                                                              Ý");
	}
	printf("Ý------------------------------------------------------------------------------Ý");
	gotoxy(2,2);
}

void lookup(int kc)
{
	switch(kc)
	{
	case 2:
		printf("1");
	case 3:
		printf("2");
	case 4:
		printf("3");
	case 5:
		printf("4");
	case 6:
		printf("5");
	case 7:
		printf("6");
	case 8:
		printf("7");
	case 9:
		printf("8");
	case 10:
		printf("9");
	case 11:
		printf("0");
	case 12:
		printf("-");
	case 13:
		printf("=");
	case 14:
		printf("\b");
	case 15:
		printf("\t");
	case 16:
		if(caps==0)
			printf("q");
		else
			printf("Q");
		break;
	case 17:
		if(caps==0)
			printf("w");
		else
			printf("W");
		break;
	case 18:
		if(caps==0)
			printf("e");
		else
			printf("E");
		break;
	case 19:
		if(caps==0)
			printf("r");
		else
			printf("R");
		break;
	case 20:
		if(caps==0)
			printf("t");
		else
			printf("T");
		break;
	case 21:
		if(caps==0)
			printf("y");
		else
			printf("Y");
		break;
	case 22:
		if(caps==0)
			printf("u");
		else
			printf("U");
		break;
	case 23:
		if(caps==0)
			printf("i");
		else
			printf("I");
		break;
	case 24:
		if(caps==0)
			printf("o");
		else
			printf("O");
		break;
	case 25:
		if(caps==0)
			printf("p");
		else
			printf("P");
		break;
	case 26:
		printf("[");
	case 27:
		printf("]");
	case 28:
		printf("\n");
	case 30:
		if(caps==0)
			printf("a");
		else
			printf("A");
		break;
	case 31:
		if(caps==0)
			printf("s");
		else
			printf("S");
		break;
	case 32:
		if(caps==0)
			printf("d");
		else
			printf("D");
		break;
	case 33:
		if(caps==0)
			printf("f");
		else
			printf("F");
		break;
	case 34:
		if(caps==0)
			printf("g");
		else
			printf("G");
		break;
	case 35:
		if(caps==0)
			printf("h");
		else
			printf("H");
		break;
	case 36:
		if(caps==0)
			printf("j");
		else
			printf("J");
		break;
	case 37:
		if(caps==0)
			printf("k");
		else
			printf("K");
		break;
	case 38:
		if(caps==0)
			printf("l");
		else
			printf("L");
		break;
	case 39:
		printf(";");
	case 40:
		printf("\'");
	case 41:
		printf("`");
	case 42:
		printf("SHIFT");
	case 43:
		printf("#");
	case 44:
		if(caps==0)
			printf("z");
		else
			printf("Z");
		break;
	case 45:
		if(caps==0)
			printf("x");
		else
			printf("X");
		break;
	case 46:
		if(caps==0)
			printf("c");
		else
			printf("C");
		break;
	case 47:
		if(caps==0)
			printf("v");
		else
			printf("V");
		break;
	case 48:
		if(caps==0)
			printf("b");
		else
			printf("B");
		break;
	case 49:
		if(caps==0)
			printf("n");
		else
			printf("N");
		break;
	case 50:
		if(caps==0)
			printf("m");
		else
			printf("M");
		break;
	case 51:
		printf(",");
	case 52:
		printf(".");
	case 53:
		printf("/");
	case 54:
		printf("SHIFT");
	case 55:
		printf("*");
	case 57:
		printf(" ");
	case 58:
		if(caps==0)
		{
			caps=1;
		}
		else
		{
			caps=0;
		}
		break;
	case 71:
		gotoxy(2,csline);
		break;
	case 72:
		printf("UP");
	case 73:
		printf("PAGE UP");
	case 74:
		printf("-");
	case 75:
		printf("LEFT");
	case 76:
		gotoxy(2,csline);
		break;
	case 77:
		printf("RIGHT");
	case 78:
		printf("+");
	case 79:
		gotoxy(76,csline);
		break;
	case 80:
		printf("DOWN");
	case 81:
		printf("PAGE DOWN");
	case 83:
		printf("DELETE");
	}
}