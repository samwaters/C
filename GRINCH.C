#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int getdist(int fromx, int fromy, int tox, int toy);

void main()
{
	int x1,y1,dist;
	int tmp;
	int posx, posy;
	int i,j;
	time_t x;
	x = time(NULL);
	srand(x);
	clrscr();
	posx = random(10);
	posy = random(10);
	gotoxy(1,1);
	for(i=2;i<11;i++)
	{
		gotoxy(i,1);
		printf("%d",i-1);
	}
	for(j=2;j<11;j++)
	{
		gotoxy(1,j);
		printf("%d",j-1);
	}
	for(i=1;i<10;i++)
	{
		for(j=1;j<10;j++)
		{
			gotoxy(i+1,j+1);
			printf("?");
		}
	}
	redo:
	gotoxy(1,11);
	printf("                 \n                    \n");
	gotoxy(1,11);
	printf("Enter Column:");
	scanf("%d",&x1);
	printf("Enter Row:");
	scanf("%d",&y1);
	dist = getdist(x1,y1,posx,posy);
	if(dist == 0)
	{
		printf("Yay!                \n");
		exit(0);
	}
	for(tmp=0;tmp<dist;tmp++)
	{
		printf("\a");
	}
	printf("%d units away.\n",dist);
	gotoxy(x1+1,y1+1);
	printf(" ");
	delay(750);
	goto redo;
}

int getdist(int fromx, int fromy, int tox, int toy)
{
	int x, y, z, a;
	x = (tox - fromx) * (tox - fromx);
	y = (toy - fromy) * (toy - fromy);
	z = x + y;
	a = sqrt(z);
	/*printf("%d %d %d %d %d %d %d %d\n",fromx,fromy,tox,toy,x,y,z,a);*/
	return a;
}

