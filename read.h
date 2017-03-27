#ifndef READ_H
#define READ_H

#include <stdio.h>

typedef struct {
	int height;
	int width;
	char **grid;
	int numberofgen;
	int print;
	int red;
	int green;
	int blue;
}option;

int read_cfg(FILE* config, option *cfg);
int read_grid(FILE* grid, option *cfg);

#endif
