#include "read.h"
#include "gen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void write(option *cfg) {
        int j,i;
        for(int i = 1;i<=cfg->width;i++){
                for( j = 0 ; j<=cfg->height;j++)
                        printf("%c ",cfg->grid[i][j]);

                printf("\n");

        }
}

int  mymemcpy(option *cfg, char** tmp) {
	int w=cfg->width;
	int h=cfg->height;
	for(int i=1;i<=cfg->height;i++) 
		for(int j=1;j<=cfg->width;i++)
			cfg->grid[i][j]=tmp[i][j];
	return 0;
}

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
	write(&cfg);
	
	mymemcpy(&cfg,generate(&cfg));

        write(&cfg);
}
