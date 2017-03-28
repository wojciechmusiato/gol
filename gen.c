#include <stdio.h>
#include <stdlib.h>
#include "read.h"

#define	GET(a,b) cfg->grid[a][b]

	int fill (option *cfg) {
		int h=cfg->height;
		int w=cfg->width;		///	grid[y][x]
		cfg->grid[0][0]=cfg->grid[h][1];
		cfg->grid[0][w+1]=cfg->grid[h][w];
		cfg->grid[h+1][0]=cfg->grid[1][1];
		cfg->grid[h+1][w+1]=cfg->grid[1][w];
		
		for(int i=1;i<=w;i++) {
			cfg->grid[0][i]=cfg->grid[h][i];
			cfg->grid[h+1][i]=cfg->grid[1][i];
		}
		for(int i=1;i<=h;i++) {
			cfg->grid[i][0]=cfg->grid[i][w];
			cfg->grid[i][w+1]=cfg->grid[i][1];
		}
		return 0;
	}
	char **generate(option *cfg) {
		
		int height = cfg->height;
		int width= cfg->width;	
		char **tmp = malloc((height+2)*sizeof(tmp));
		for(int i = 0 ; i <= width+1 ; i++)  			  
			tmp[i] = malloc((width+2)*sizeof(tmp[i]));
		
		int i,j;
		int s=0;
		for(i=1;i<=10;i++) {
			for(j=1;j<=10;j++) {
				if (GET(i-1,j-1)=='+')
					s++;			
				if (GET(i-1,j)=='+')
					s++;			
				if (GET(i-1,j+1)=='+')
					s++;
							
				if (GET(i,j-1)=='+')
					s++;			
			
				if (GET(i,j)=='+')
					s++;			

				if (GET(i,j+1)=='+')
					s++;			
			
				if (GET(i+1,j-1)=='+')
					s++;	
						
				if (GET(i+1,j)=='+')
					s++;			
				
				if (GET(i+1,j+1)=='+')
					s++;	
				if (s>=2)
					tmp[i][j]='+';
				else 
					tmp[i][j]='-';		
			}
		return tmp;
		}
	}
