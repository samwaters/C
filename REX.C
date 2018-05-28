#include <stdio.h>

#define BASE 0x1000000

void wtr();
void rfr();

void main()
{
	int ms;
	redo:
	printf("\n---Menu---\n1.Write to RAM\n2.Read from RAM\n3.Exit\nMake a selection:");
	scanf("%d", &ms);
	switch(ms)
	{
		case 1:
			wtr();
			break;
		case 2:
			rfr();
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("INVALID SELECTION\a\n\n");
			goto redo;
	}
}

void wtr()
{
	char msg[3000],b;
	int a=0;
	int long i,j;
	b = 'z';
	printf("Enter a message to write to RAM:");
	while(b != 13)
	{
		b=getche();
		if(b == 9)
		{
			if(a > 0)
			{
				a--;
			}
		}
		else
		{
			msg[a] = b;
			a++;
		}
	}
	msg[a] = '\0';
	a++;
	printf("\n");
	for(i=0;i<a;i++)
	{
		j = BASE + i;
		setmem((void *)j, 1, msg[i]);
	}
}

void rfr()
{
	char far *ptr;
	char x;
	int i;
	printf("Message read:");
	for(i=0;i<3000;i++)
	{
		ptr = (char far *)BASE + i;
		x = *ptr;
		if(x != '\0')
			printf("%c",x);
		else
		{
			printf("\n");
			return;
		}
	}
}