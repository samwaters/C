#include <stdio.h>
#include <dos.h>
#include <mem.h>

char far *OldData;
char OD;

void main()
{
	int long start, end,i,ec;
	char far *ptr;
	char x;
	ec=0;
	clrscr();
	printf("Enter start block:");
	scanf("%li",&start);
	printf("Enter end block:");
	scanf("%li",&end);
	for(i=start;i<=end;i++)
	{
		OldData = (char far *)i;
		OD = *OldData;
		setmem((void *)i,1,'A');
		ptr = (char far *)i;
		x = *ptr;
		if(x != 'A')
		{
			printf("Error Reading / Writing Block %li\n",i,x);
			ec++;
		}
		gotoxy(1,3);
		printf("Testing Block %ld of %ld",i,end);
		setmem((void *)i,1,OD);
		delay(20);
	}
	printf("\nRAM Test Completed. There were %d Errors.\n\n",ec);
}