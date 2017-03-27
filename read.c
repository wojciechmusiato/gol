#include "read.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int read_grid(FILE* grid, option *cfg){
	int i=0;
	int j=0;
	int c;
	int width=0;
	int height=0;
	while((c = fgetc(grid))!= EOF){
		if(c == '\n')
			height++;
		if(((c=='-')||c=='+') && height == 1)
			width++;
	}
	cfg->width = width;
	cfg->height = height;
	rewind(grid);
	cfg->grid = malloc(height*sizeof(cfg->grid));
	for(i = 0 ; i < width ; i++)
		cfg->grid[i] = malloc(width*sizeof(cfg->grid[i]));
	i=0;
	j=0;
	while((c = fgetc(grid))!=EOF){
		if(c=='-'){
			cfg->grid[i][j] = '-';
			j++;
		}else if(c=='+'){
			cfg->grid[i][j] = '+';
			j++;
		}else if(c=='\n'){
			i++;
			j=0;
		}
	}		
	return 0;
}
int read_cfg(FILE* config, option *cfg){
	int c;
	int i;
	int v[4];
	for(i=0;i<4;i++){
		while(isdigit(c=fgetc(config))==0&&c!=EOF)
			;
		fseek(config, -1, SEEK_CUR);
		if (fscanf( config, "%d",  &v[i] ) !=1)
			return -1;
	}
	cfg->numberofgen=v[0];
	cfg->print=v[1];
	cfg->red=v[2];
	cfg->green=v[3];
	cfg->blue=v[4];
	return 0;
}
