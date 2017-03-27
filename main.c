#include "read.h"
#include <stdio.h>
#include <stdlib.h>


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
	for(int i = 0;i<10;i++){
		for(int j = 0 ; j<10 ;j++)
			printf("%c",cfg.grid[i][j]);
		
		printf("\n");
	}
}