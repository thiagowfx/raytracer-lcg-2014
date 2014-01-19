#include <cstdio>
#include "pngpp.h"
#include "World.h"

int main() {
  FILE *fp;

  /* World processing */
  fp = fopen("world_output.txt", "w");

  if (fp != NULL) {
    World w;
    w.build();
    w.render_scene(fp);
    fclose(fp);
  }

  /* Image rendering */
  fp = fopen("world_output.txt","r");

  if (fp != NULL) {
    file_to_png(fp, (char *) "output.png");  
    fclose(fp);
  }

  return 0;
}
