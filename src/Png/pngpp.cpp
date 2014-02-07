/**
 * Compilar com:
 * g++ pngpp.cpp -o pngpp -Wall $(libpng-config --cflags) $(libpng-config --ldflags)
 *
 */

#include "pngpp.h"

void generate_sample_image(size_t width, size_t height) {
  png::image< png::rgb_pixel > image(width, height);

  /* de baixo para cima, da esquerda para a direita */
  for (size_t y = 0; y < image.get_height(); ++y) {
    for (size_t x = 0; x < image.get_width(); ++x) {
      if (x < image.get_width() / 2)
	image[y][x] = png::rgb_pixel(255, 0, 0);
      else
	image[y][x] = png::rgb_pixel(0, 0, 255);
    }
  }
  image.write("sample.png");
}


void file_to_png(FILE *fp, char *imageFile) {
  unsigned width, height, r, g, b, x, y;

  
  /* Read size parameters */
  fscanf(fp, "%d %d\n", &width, &height);
  // ++width, ++height;		// to avoid buffer overflows

  
  /* Render the image */
  png::image< png::rgb_pixel > image(width, height);
  while ( fscanf(fp, "%u %u %u %u %u\n", &x, &y, &r, &g, &b) == 5 ) {
    image[y][x] = png::rgb_pixel(r, g, b);
  }

  /* Actually write the image to the file */
  image.write(imageFile);
}
