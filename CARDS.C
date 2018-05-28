#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int cards[52];
int suit[52];

void shuffle();

void main()
{
	int i;
	shuffle();
	for(i=0;i<52;i++)
	{
		printf("(%d of %d) - ",cards[i],suit[i]);
	}
	printf("\n\n");
}

void shuffle()
{
	time_t thetime;
	int a,b,c,pia;
	int addit;
	thetime = time(NULL);
	srand(thetime);
	for(pia=0;pia<52;pia++)
	{
		newcard:
		addit=1;
		a = random(13) + 1;
		b = random(4) + 1;
		for(c=0;c<pia;c++)
		{
			if((cards[c]==a) && (suit[c]==b))
			{
				addit=0;
			}
		}
		if(addit==1)
		{
			cards[pia] = a;
			suit[pia] = b;
		}
		else
			goto newcard;
	}
}
