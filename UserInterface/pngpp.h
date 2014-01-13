/**
 * Compilar com:
 * g++ pngpp.cpp -Wall $(libpng-config --cflags) $(libpng-config --ldflags)
 *
 */

#include <cstring>
#include <png++/png.hpp>

void generate_image(size_t width, size_t height) {
  png::image< png::rgb_pixel > image(width, height);

  // de baixo para cima, da esquerda para a direita
  for (size_t y = 0; y < image.get_height(); ++y) {
    for (size_t x = 0; x < image.get_width(); ++x) {
      if (x < image.get_width() / 2)
	image[y][x] = png::rgb_pixel(255, 0, 0);
      else
	image[y][x] = png::rgb_pixel(0, 0, 255);
    }
  }
  
  image.write("output.png");
}
