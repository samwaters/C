#include <stdio.h>
#include <time.h>
#define COM1 0x3F8

char rdat[32767];
int store;

void main()
{
	int tmp,pt,tp;
	FILE *fhandle;
	char fname[30];
	pt = 0;
	printf("Enter file name AND path:");
	scanf("%s",fname);
	fhandle = fopen(fname,"a+");
	while(tmp != 27) /*Has file finished*/
	{
		tmp = inportb(COM1);
		if(tmp != store) /*Have we already had this piece?*/
		{
			if(tmp < 250) /*Is this useless data?*/
			{
				if(tmp != 27) /*Is this Esc character?*/
				{
					rdat[pt] = tmp; /*Add to array*/
					printf("%c",tmp, tmp);
					pt++;
				}
			}
		store = tmp;
		}
	}
	for(tp = 0; tp < pt; tp++)
	{
		fprintf(fhandle, "%c", rdat[tp]); /*Write array to file*/
	}
	fclose(fhandle);
}