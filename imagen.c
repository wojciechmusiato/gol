#include "lodepng.h"
#include "read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height)
{
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename, image, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
}

int makeimage(option *cfg,int nrgen){
    int k=10;
	unsigned width = cfg->width*k, height = cfg->height*k;
	unsigned char* image = malloc(width * height * 4);
	unsigned x, y;
    char filename[10];
    sprintf(filename, "result/image%d", nrgen);
	int i,j;

	for(y = 0 ; y < height ; y++ ) 
 		for(x = 0; x < width; x++) {
			image[4 * width * y + 4 * x + 0] = 255;
			image[4 * width * y + 4 * x + 1] = 255;
			image[4 * width * y + 4 * x + 2] = 255;
			image[4 * width * y + 4 * x + 3] = 255;
		}
	for(i=0;i<cfg->height;i++){
		for(j=0;j<cfg->width;j++){
			if(cfg->grid[i+1][j+1]=='+'){
				for(int n=0;n<k;n++){
					for(int m=0;m<k;m++){
						image[4 * width * (i*k+n) + 4 * (j*k+m) + 0]  = 0;
						image[4 * width * (i*k+n) + 4 * (j*k+m) + 1]  = 25;
						image[4 * width * (i*k+n) + 4 * (j*k+m) + 2]  = 125;
						image[4 * width * (i*k+n) + 4 * (j*k+m) + 3]  = 255;
					}
				}
			}
		}
	}
	
  encodeOneStep(filename, image, width, height);

  free(image);
  return 0;
}
