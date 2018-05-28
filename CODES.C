#include <stdio.h>
#include <time.h>

void main()
{
	int a,b,c,d,e,f,g,h;
	clock_t t1;
	int td;
	for(a=48;a<91;a++)
	{
		if(a==58)
			a=65;
		for(b=48;b<91;b++)
		{
			if(b==58)
				b=65;
			for(c=48;c<91;c++)
			{
				if(c==58)
					c=65;
				for(d=48;d<91;d++)
				{
					if(d==58)
						d=65;
					for(e=48;e<91;e++)
					{
						if(e==58)
							e=65;
						for(f=48;f<91;f++)
						{
							if(f==58)
								f=65;
							for(g=48;g<91;g++)
							{
								if(g==58)
									g=65;
								for(h=48;h<91;h++)
								{
									if(h==58)
										h=65;
									printf("%c%c%c%c%c%c%c%c\n",a,b,c,d,e,f,g,h);
								}
							}
						}
					}
				}
			}
		}
	}
	t1=clock();
	td=t1/18.2;
	printf("\nTook %.2d\n",td);
}
