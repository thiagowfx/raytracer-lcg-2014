#include "World.h"
#include <cstdio>

const char world_output[] = "world_output.txt";
const char image_output[] = "image_output.png";

void build_world();


int main() {
  build_world();
  
  return 0;
}


void build_world() {
  FILE *fp;
  World w;

  /* Set up and execute the Raytracer */
  if ( (fp = fopen("world_output.txt", "w")) != NULL) {
    w.build();

    if (w.tracer_ptr == NULL)
      runtime_error("ERROR: No world tracer set.");
   
    // w.render_scene(fp);
    w.camera_ptr->render_scene(w, fp);
    fclose(fp);
  }
  else
    runtime_error("ERROR: Cannot open the file");
  
  /* Image Rendering */
  if ( (fp = fopen(world_output,"r")) != NULL ) {
    w.file_to_png(fp, image_output);
    fclose(fp);
  }
  else
    runtime_error("ERROR: Cannot open the file");
  
}
