#include <stdio.h>
#include <dos.h>

void main()
{
	int long end,i,ec;
	char far *ptr;
	char x,fname[30];
	FILE *fh;
	ec = 0;
	clrscr();
	printf("Enter amount of RAM to read (MB):");
	scanf("%li",&end);
	end = end * 1024 * 1024;
	printf("Enter filename and path to save to:");
	scanf("%s",fname);
	fh = fopen(fname,"a+");
	printf("---BEGIN RAM DUMP---\n");
	for(i=0;i<end;i++)
	{
		ptr = (char far *)i;
		x = *ptr;
		fprintf(fh,"%c",x);
		printf("Byte %ld of %ld",i,end);
		gotoxy(1,4);
		ec++;
	}
	printf("\n---END RAM DUMP---\nBytes Written: %ld",ec);
}