#include <stdio.h>
#include <graphics.h>
#include <math.h>

#define PI 3.14159265359

void main()
{
	int gd=DETECT, gm=VGAHI;
	int poly[9];
	float i,j,ox,oy;
	initgraph(&gd,&gm,"");
	setfillstyle(LTSLASH_FILL,2);
	ox=0;
	oy=235;
	for(i=0;i<651;i++)
	{
		j=235-(sin((i * PI) / 180)) * 100;
		line(ox,oy,i,j);
		ox=i;
		oy=j;
	}
	ox=0;
	oy=235;
	for(i=0;i<651;i++)
	{
		j=235-(cos((i * PI) / 180) * 100);
		line(ox,oy,i,j);
		ox=i;
		oy=j;
	}
	ox=0;
	oy=235;
	for(i=0;i<651;i++)
	{
		j=235+(sin((i * PI) / 180) * 100);
		line(ox,oy,i,j);
		ox=i;
		oy=j;
	}
	ox=0;
	oy=235;
	for(i=0;i<651;i++)
	{
		j=235+(cos((i * PI) / 180) * 100);
		line(ox,oy,i,j);
		ox=i;
		oy=j;
	}
	poly[0]=0;
	poly[1]=235;
	poly[2]=45;
	poly[3]=235-((1/sqrt(2)) * 100);
	poly[4]=90;
	poly[5]=235;
	poly[6]=45;
	poly[7]=235-(-(1/sqrt(2)) * 100);
	poly[8]=0;
	poly[9]=235;
	fillpoly(4,poly);
	printf("%f",(22.5 * (1/sqrt(2))) * 4);
}