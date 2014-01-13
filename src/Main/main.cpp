#include <cstdio>
#include "pngpp.h"
#include "World.h"

int main() {

  /* World */
  World *w;
  
  w = new World();
  w->build();

  FILE *fp = fopen("world_output.txt", "w");
  w->render_scene(fp);
  fclose(fp);

  /* Render the image */
  FILE *fp2 = fopen("world_output.txt","r");

  if (fp2 != NULL) {
    file_to_png(fp2);  
    fclose(fp2);
  } else
    printf("File not found.\n");

  return 0;
}
