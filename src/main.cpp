#include "World.h"
#include "pngpp.h"
#include <cstdio>

int main() {
  FILE *fp;

  /* World processing */
  fp = fopen("world_output.txt", "w");

  if (fp != NULL) {
    World w;
    w.build();

    /* Check if tracer from the build function is not null */
    if (w.tracer_ptr == NULL) {
      printf("You forgot to set a world tracer!\n");
      return 1;
    }     
   
    w.render_scene(fp);
    // w.render_perspective(fp);
    fclose(fp);
  }

  /* Image rendering */
  fp = fopen("world_output.txt","r");

  if (fp != NULL) {
    file_to_png(fp, "output.png");  
    fclose(fp);
  }

  return 0;
}
