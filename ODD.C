#include <stdio.h>
#include <math.h>
#include <graphics.h>

#define PI 3.14159265359

void main()
{
	/*dy/dx of SIN(x) = COS(x)*/
	/*dy/dx of TAN(x) = 1/(SIN^2(x))*/
	float x, C, S, T;
	int gd=DETECT, gm=IBM8514HI;
	initgraph(&gd,&gm,"");
	for(x=0;x<91;x++)
	{
		C = cos((x * PI) / 180);
		S = sin((x * PI) / 180);
		T = tan((x * PI) / 180);
		putpixel(x*6,435-(C * 400),15);
		putpixel(x*6,435-(S * 400),15);
		putpixel(x*6,435-(T * 400),15);
		if((S == T) && (S == C))
			printf("%.0f ",x);
	}
}