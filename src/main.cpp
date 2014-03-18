#include "World.h"
#include <cstdio>

/* Builds the Ray Tracer */
void build_raytracer();


int main() {
  build_raytracer();
  
  return 0;
}


void build_raytracer() {
  
  FILE *fp;
  World w;

  /* World processing */
  if ( (fp = fopen("world_output.txt", "w")) != NULL) {
    w.build();

    if (w.tracer_ptr == NULL) {
      puts("ERROR: You forgot to set a world tracer");
      exit(1);
    }     
   
    // w.render_scene(fp);
    w.camera_ptr->render_scene(w, fp);
    fclose(fp);
  }
  else {
    puts("ERROR: Can't open the file");
    exit(1);
  }
  
  /* Image rendering */
  if ( (fp = fopen("world_output.txt","r")) != NULL) {
    w.file_to_png(fp, "output.png");  
    fclose(fp);
  }
  else {
    puts("ERROR: Can't open the file");
    exit(1);
  }
}
