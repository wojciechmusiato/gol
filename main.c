#include "read.h"
#include "gen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char**argv){
	FILE* config = fopen("config.cfg","r");
	FILE* grid = fopen("gen.cfg","r");
	if(config == NULL || grid == NULL){
		fprintf(stderr, "error, unable to read one of these files: %s, %s\n","config.cfg","gen.cfg");
		return EXIT_FAILURE;
	}
	option cfg;
	if(read_grid(grid, &cfg) == 1){
		fprintf(stderr,"error, unable to read information from grid.cfg");
		return EXIT_FAILURE;
	}
	if(read_cfg(config, &cfg) == 1){
		fprintf(stderr,"error, unable to read information from grid.cfg");
		return EXIT_FAILURE;
	}
	fill(&cfg);
	int j;
	for(int i = 0;i<=cfg.width+1;i++){
		for( j = 0 ; j<=cfg.height+1;j++)
			printf("%c ",cfg.grid[i][j]);
		
		printf("\n");

	}
    int i;
printf("%d to wysokosc, %d to szerokosc, %d to j",cfg.height,cfg.width,j);

    if(cfg.print=0){
        for(i=1;i<=cfg.numberofgen;i++){
            memcpy(cfg.grid,generate(&cfg),(width+2)*(height+2)*sizeof(char));
            makeimage(&cfg ,i, cfg.grid);
        }
    }else{
        for(i=1;i<=cfg.numberofgen;i++){
            memcpy(cfg.grid,generate(&cfg),(width+2)*(height+2)*sizeof(char));
            if(cfg.print==i)
                makeimage(&cfg ,i, cfg.grid);
    }
}


