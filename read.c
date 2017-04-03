#include "read.h"

#include <time.h>
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
	        if((c!='-')&&(c!=' ')&&(c!='+')&&(c!='\n')) return 1;
	}
    if(width==0||height==0) return 1;
	cfg->width = width;
	cfg->height = height;
	rewind(grid);

    cfg->grid = malloc((height+2)*sizeof(char**));  //+2 bo jeszcze powloka

	for(i = 0 ; i <= height+1 ; i++)  			  
	    cfg->grid[i] = malloc((width+2)*sizeof(char*));

	i=1;		// 	oś	y
	j=1;		//	oś	x	

	while((c = fgetc(grid))!=EOF){
		if(c=='-'){
			cfg->grid[i][j] = '-';
			j++;
		}else if(c=='+'){
			cfg->grid[i][j] = '+';
			j++;
		}else if(c=='\n'){
			i++;
			j=1;;
		}
	}		
	return 0;
	}
int read_cfg(FILE* config, option *cfg){
	int c;
	int i;
	int v[5];
	for(i=0;i<5;i++){
		while(isdigit(c=fgetc(config))==0&&c!=EOF)
			;
		fseek(config, -1, SEEK_CUR);
		if (fscanf( config, "%d",  &v[i] ) !=1)
			return 1;
	}
	cfg->numberofgen=v[0];
	cfg->print=v[1];
	cfg->red=v[2];
	cfg->green=v[3];
	cfg->blue=v[4];
	return 0;
}
int rand_grid(option *cfg, int h, int w) {
	int i,j,tmp;	
	srand(time(0));
	cfg->height=h;
	cfg->width=w;
	cfg->grid = malloc((h+2)*sizeof(char**));  //+2 bo jeszcze powloka
	for(i = 0 ; i <= h+1 ; i++)  			  
	    	cfg->grid[i] = malloc((w+2)*sizeof(char*));
	for(i=1;i<=h;i++) {
		for(j=1;j<=w;j++) {	
		cfg->grid[i][j]= ((rand()%2) == 0) ? '+' : '-';
		}
	}
	return 0;
}
