#include <stdio.h>
#include <stdlib.h>
#include "read.h"
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
	}
