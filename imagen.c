#include "lodepng.h"
#include "read.h"
#include <stdio.h>
#include <stdlib.h>
void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height)
{
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename, image, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
}

int generate(option *cfg){
	unsigned width = cfg->width*5, height = cfg->height*5;
	unsigned char* image = malloc(width * height * 4);
	unsigned x, y;
	int i,j;

	for(y = 0 ; y < height ; y++ ) 
 		for(x = 0; x < width; x++) {
			image[4 * width * y + 4 * x + 0] = 255;
			image[4 * width * y + 4 * x + 1] = 255;
			image[4 * width * y + 4 * x + 2] = 255;
			image[4 * width * y + 4 * x + 3] = 255;
		}
	for(i=0;i<cfg->height;i++){
		for(j=0;i<cfg->width;j++){
			if(cfg>grid[i][j]=='+'){
				for(int n=0;n<5;n++){
					for(int m=0;m<5;m++){
						image[4 * width * (i*5+n) + 4 * (j*5+m) + 0]  = 255;
						image[4 * width * (i*5+n) + 4 * (j*5+m) + 0]  = 25;
						image[4 * width * (i*5+n) + 4 * (j*5+m) + 0]  = 125;
						image[4 * width * (i*5+n) + 4 * (j*5+m) + 0]  = 255;
					}
				}
			}
		}
	}
	
  encodeOneStep(filename, image, width, height);

  free(image);
  return 0;
}
