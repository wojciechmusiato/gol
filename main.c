#include "read.h"
#include "gen.h"
#include "imagen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void write(option *cfg, int k) {
        int j,i;					// k to paramter , jesli = 1 to wypisuje z powloka, jesli 0 to bez
        for(int i = 1-k;i<=cfg->height+k;i++){
                for( j = 1-k ; j<=cfg->width+k;j++)
                        printf("%c ",cfg->grid[i][j]);

                printf("\n");

        }
	printf("\n\n");
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
	write(&cfg,1);

	generate(&cfg);
    makeimage(&cfg,1);
		
}
