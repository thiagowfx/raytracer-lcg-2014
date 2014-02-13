#include "World.h"
#include <cstdio>

int main() {
  FILE *fp;
  World w;

  /* World processing */
  if ( (fp = fopen("world_output.txt", "w")) != NULL) {
    w.build();

    if (w.tracer_ptr == NULL) {
      printf("ERROR: You forgot to set a world tracer!\n");
      return 1;
    }     
   
    w.render_scene(fp);
    // w.render_perspective(fp);
    fclose(fp);
  }

  /* Image rendering */
  if ( (fp = fopen("world_output.txt","r")) != NULL) {
    w.file_to_png(fp, "output.png");  
    fclose(fp);
  }

  return 0;
}
