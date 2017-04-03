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
	printf("\n");
}

int main(int argc, char**argv){
	option cfg;
	FILE* config = fopen("config.cfg","r");
	if ((argc==1)||(strcmp(argv[1], "-rand") !=0)) {
		FILE* grid = argc==1 ? fopen("gen.cfg","r") : fopen(argv[1],"r");
		if(grid ==NULL) {
			fprintf(stderr,"error, unable to read %s \n",argc==1 ? "gen.cfg" : argv[1]);
			return EXIT_FAILURE;
		}
		if(read_grid(grid, &cfg) == 1){
			fprintf(stderr,"error, unable to read %s \n",argc==1 ? "gen.cfg" : argv[1]);
			return EXIT_FAILURE;
		}	
	}
	else {
		if(argc != 4) {
			fprintf(stderr,"error, incorrect arguments");
			return EXIT_FAILURE;
		}
		rand_grid(&cfg,atoi(argv[2]),atoi(argv[3]));			
	}

	if(config == NULL){
		fprintf(stderr, "error, unable to read : %s\n","config.cfg");
		return EXIT_FAILURE;
	}
	
	if(read_cfg(config, &cfg) == 1){
		fprintf(stderr,"error, unable to read information from config.cfg \n");
		return EXIT_FAILURE;
	}
    if(cfg.red<0||cfg.red>255||cfg.green<0||cfg.green>255||cfg.blue<0||cfg.blue>255){
        cfg.red=0;
        cfg.green=0;
        cfg.blue=0;    
    }
	printf("\nGeneration read from file:\n");
	write(&cfg,0);
	int i;
	makeimage(&cfg,0);
   	if(cfg.print==0){
        	for(i=1;i<=cfg.numberofgen;i++){
	       		fill(&cfg);
            		generate(&cfg);
            		makeimage(&cfg,i);
       		}
        }else if (cfg.print >0 && cfg.print <cfg.numberofgen){
       		fill(&cfg);
        	generate(&cfg);
           	makeimage(&cfg,cfg.print);
        }else{
        	fprintf(stderr,"error, the number of generation you wanted to print is invalid: %d",cfg.print);
    	}
	printf("Your chosen generations have been successfully saved in folder \\result\n");	
        return EXIT_SUCCESS;
}  
