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
    if ((argc==2)&&(strcmp(argv[1], "-help") ==0)){
        printf("Gra w zycie 1.0 \n\
OPIS\n\
Gra w zycie - jeden z pierwszych i najbardziej znanych przykladow automatu komorkowego, wymyślony w roku 1970 przez brytyjskiego matematyka Johna Conwaya. Gra toczy się na planszy podzielonej na kwadratowe komorki. Kazda komorka ma osmiu „sasiadow” czyli komórki przylegajace do niej bokami i rogami. Kazda komorka moze znajdowac sie w jednym z dwoch stanow: moze być albo „zywa” (wlaczona), albo „martwa” (wylączona). Stany komorek zmieniaja sie w pewnych jednostkach czasu. W kolejnych generacjach wszystkie komorki zmieniaja swoj stan dokladnie w tym samym momencie. Stan danej komorki zalezy od liczby jej zywych sąsiadow.\n\
Martwa komorka, ktora ma dokladnie 3 żywych sąsiadow, staje się zywa w nastepnej jednostce czasu (rodzi sie)\n\
Zywa komorka z 2 albo 3 zywymi sasiadami pozostaje nadal zywa; przy innej liczbie sasiadow umiera (z „samotnosci” albo „zatloczenia”).\n \n\
KONFIGURACJA\n\
W pliku config.cfg mozna konfigurowac nastepujace parametry:\n\
numberofgen - liczba generacji, ktore chcemy symulowac;\n\
print - numer generacji, ktorego graficzna reprezentacje chcemy zobaczyc. Dla wartosci ”0” wszystkie generacje są eksportowane do plikow png;\n\
red,green,blue - przyjmuja wartosci od 0 do 255, ktore ustawiaja kolor zywych komorek na obrazkach.\n\
Plik gen.cfg zawiera uklad komorek, na podstawie ktorej symulowane sa kolejne generacje. Komorki reprezentuje macierz znakow plus i minus, gdzie ”-” uchodzi za martwa komorkę, a ”+” zywa.\n\n\
UZYCIE\n\
./Gameoflife [-help] [-rand <width> <height>] [*.cfg]\n\n\
Po wywolaniu w folderze ./result pojawia sie wybrane symulowane generacje\n\n\
OPCJE\n\
-help - pomoc\n\
-rand <height> <width> - losowanie konfiguracji planszy o danej wysokosci i szerokosci\n\
*.cfg - argument wskazujacy na plik zawierajacy plansze\n");
return 0;
                
    }else if ((argc==1)||(strcmp(argv[1], "-rand") !=0)) {
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
	if ((argc==1)||(strcmp(argv[1], "-rand") !=0)) 
		printf("\nGeneration read from file:\n");
	else 
		printf("\nGeneration chosen randomly:\n");
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
