#include "lodepng.h"

#include <stdio.h>
#include <stdlib.h>
void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height)
{
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename, image, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
}

int main(int argc, char *argv[])
{
  const char* filename = argc > 1 ? argv[1] : "test.png";

  unsigned width = 512, height = 512;
  unsigned char* image = malloc(width * height * 4);
  unsigned x, y;
  for(y = 0 ; y < height ; y++ ) 
 	 for(x = 0; x < width; x++) {
		image[4 * width * y + 4 * x + 0] = 255;
		image[4 * width * y + 4 * x + 1] = 255;
		image[4 * width * y + 4 * x + 2] = 255;
		image[4 * width * y + 4 * x + 3] = 255;
	}
  for(y = 0 ; y < height ; y=y+5 ) 
 	 for(x = 0; x < width; x=x+2) {
		image[4 * width * y + 4 * x + 0] = 255;
		image[4 * width * y + 4 * x + 1] = 25;
		image[4 * width * y + 4 * x + 2] = 125;
		image[4 * width * y + 4 * x + 3] = 255;
}
  encodeOneStep(filename, image, width, height);

  free(image);
  return 0;
}
