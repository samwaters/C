#include <stdio.h>

int lkey;
char lookup(int kc);
void main()
{
	int a;
	char b;
	a=0;
	while(a != 1)
	{
		a = inportb(0x60);
		if(a != lkey)
		{
			if(a < 100)
			{
				b = lookup(a);
				if(b != '~')
					printf("%c",b);
				}
		lkey=a;
		}
	}
}


char lookup(int kc)
{
	switch(kc)
	{
	case 2:
		return '1';
	case 3:
		return '2';
	case 4:
		return '3';
	case 5:
		return '4';
	case 6:
		return '5';
	case 7:
		return '6';
	case 8:
		return '7';
	case 9:
		return '8';
	case 10:
		return '9';
	case 11:
		return '0';
	case 12:
		return '-';
	case 13:
		return '=';
	case 14:
		return '\b';
	case 15:
		return '\t';
	case 16:
		return 'Q';
	case 17:
		return 'W';
	case 18:
		return 'E';
	case 19:
		return 'R';
	case 20:
		return 'T';
	case 21:
		return 'Y';
	case 22:
		return 'U';
	case 23:
		return 'I';
	case 24:
		return 'O';
	case 25:
		return 'P';
	case 26:
		return '[';
	case 27:
		return ']';
	case 28:
		return '\n';
	case 29:
		printf("CTRL");
		return '~';
	case 30:
		return 'A';
	case 31:
		return 'S';
	case 32:
		return 'D';
	case 33:
		return 'F';
	case 34:
		return 'G';
	case 35:
		return 'H';
	case 36:
		return 'J';
	case 37:
		return 'K';
	case 38:
		return 'L';
	case 39:
		return ';';
	case 40:
		return '\'';
	case 41:
		return '`';
	case 42:
		printf("SHIFT");
		return '~';
	case 43:
		return '#';
	case 44:
		return 'Z';
	case 45:
		return 'X';
	case 46:
		return 'C';
	case 47:
		return 'V';
	case 48:
		return 'B';
	case 49:
		return 'N';
	case 50:
		return 'M';
	case 51:
		return ',';
	case 52:
		return '.';
	case 53:
		return '/';
	case 54:
		printf("SHIFT");
		return '~';
	case 55:
		return '*';
	case 56:
		printf("ALT");
		return '~';
	case 57:
		return ' ';
	case 58:
		printf("CAPS");
		return '~';
	case 59:
		printf("F1");
		return '~';
	case 60:
		printf("F2");
		return '~';
	case 61:
		printf("F3");
		return '~';
	case 62:
		printf("F4");
		return '~';
	case 63:
		printf("F5");
		return '~';
	case 64:
		printf("F6");
		return '~';
	case 65:
		printf("F7");
		return '~';
	case 66:
		printf("F8");
		return '~';
	case 67:
		printf("F9");
		return '~';
	case 68:
		printf("F10");
		return '~';
	case 69:
		printf("NUM");
		return '~';
	case 70:
		printf("SCROLL");
		return '~';
	case 71:
		printf("HOME");
		return '~';
	case 72:
		printf("UP");
		return '~';
	case 73:
		printf("PAGE UP");
		return '~';
	case 74:
		return '-';
	case 75:
		printf("LEFT");
		return '~';
	case 76:
		printf("HOME");
		return '~';

	case 77:
		printf("RIGHT");
		return '~';
	case 78:
		return '+';
	case 79:
		printf("END");
		return '~';
	case 80:
		printf("DOWN");
		return '~';
	case 81:
		printf("PAGE DOWN");
		return '~';
	case 82:
		printf("INSERT");
		return '~';
	case 83:
		printf("DELETE");
		return '~';
	case 87:
		printf("F11");
		return '~';
	case 88:
		printf("F12");
		return '~';
	default:
		return '~';
	}
}