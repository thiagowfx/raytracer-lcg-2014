#include "World.h"

/* tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
   ambient_ptr is set to a default ambient light because this will do for most scenes
   camera_ptr is set to NULL because the build functions will always have to construct a camera
   and set its parameters */

World::World(void) :
  background_color(),
  tracer_ptr(NULL),
  ambient_ptr(new Ambient),
  camera_ptr(NULL)
{}


World::~World(void) {		
  if(tracer_ptr) {
    delete tracer_ptr;
    tracer_ptr = NULL;
  }
	
		
  if (ambient_ptr) {
    delete ambient_ptr;
    ambient_ptr = NULL;
  }
			
		
  if (camera_ptr) {
    delete camera_ptr;
    camera_ptr = NULL;
  }
	
  delete_objects();	
  delete_lights();				
}


/* This uses orthographic viewing along the zw axis */
void World::render_scene(FILE *fp) const {

  RGBColor pixel_color;	 	
  Ray	   ray;					
  float	   zw	= 100.0;	// hardwired in
  ray.d = Vector3d(0.0, 0.0, -1.0);
  Vector2d pp;
  fprintf(fp, "%d %d\n", vp.hres, vp.vres);

  for (int r = 0; r < vp.vres; r++) // up
    for (int c = 0; c < vp.hres; c++) { // across
      pp(0) = vp.s * (c - vp.hres / 2.0 + 0.5);
      pp(1) = vp.s * (r - vp.vres / 2.0 + 0.5);
      ray.o = Vector3d( pp(0), pp(1), zw);
      pixel_color = tracer_ptr->trace_ray(ray);
      display_pixel(r, c, pixel_color, fp);
    }
}


RGBColor World::max_to_one(const RGBColor& c) const  {
  float max_value = max(c.r, max(c.g, c.b));
	
  if (max_value > 1.0)
    return (c / max_value);
  else
    return c;
}


/* Set color to red if any component is greater than one */
RGBColor World::clamp_to_color(const RGBColor& raw_color) const {
  RGBColor c(raw_color);
	
  if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
    c.r = 1.0; c.g = 0.0; c.b = 0.0;
  }
		
  return c;
}


/* raw_color is the pixel color computed by the ray tracer
   its RGB floating point components can be arbitrarily large
   mapped_color has all components in the range [0, 1], but still floating point
   display color has integer components for computer display
   the Mac's components are in the range [0, 65535]
   a PC's components will probably be in the range [0, 255]
   the system-dependent code is in the function convert_to_display_color
   the function SetCPixel is a Mac OS function */
void World::display_pixel(const int row, const int column, const RGBColor& raw_color, FILE *fp) const {
  RGBColor mapped_color;

  if (vp.show_out_of_gamut)
    mapped_color = clamp_to_color(raw_color);
  else
    mapped_color = max_to_one(raw_color);
	
  if (vp.gamma != 1.0)
    mapped_color = mapped_color.powc(1.0 / vp.gamma);
	
  //have to start from max y coordinate to convert to screen coordinates
  int x = column;
  int y = vp.vres - row - 1;

  fprintf(fp, "%d %d %d %d %d\n", x, y, (int)(mapped_color.r * 255), (int)(mapped_color.g * 255), (int)(mapped_color.b * 255));
}


ShadeRec World::hit_objects(const Ray& ray) {
  ShadeRec sr(*this); 
  double   t;
  Vector3d normal;
  Vector3d local_hit_point;
  float	   tmin        = kHugeValue;
  int 	   num_objects = objects.size();
	
  for (int j = 0; j < num_objects; j++)
    if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
      sr.hit_an_object = true;
      tmin 	       = t;
      sr.material_ptr  = objects[j]->get_material();
      sr.color         = objects[j]->get_color();
      sr.hit_point     = ray.o + t * ray.d;
      normal 	       = sr.normal;
      local_hit_point  = sr.local_hit_point;
    }
  
  if(sr.hit_an_object) {
    sr.t = tmin;
    sr.normal = normal;
    sr.local_hit_point = local_hit_point;
  }
		
  return sr;
}


/* Deletes the objects in the objects array, and erases the array.
   The objects array still exists, because it's an automatic variable, but it's empty */
void World::delete_objects(void) {
  int num_objects = objects.size();
	
  for (int j = 0; j < num_objects; j++) {
    delete objects[j];
    objects[j] = NULL;
  }	
	
  objects.erase (objects.begin(), objects.end());
}


void World::delete_lights(void) {
  int num_lights = lights.size();
	
  for (int j = 0; j < num_lights; j++) {
    delete lights[j];
    lights[j] = NULL;
  }	
	
  lights.erase (lights.begin(), lights.end());
}


/* Creates a PNG file from a world output file. */
void World::file_to_png(FILE *fp, const char *imageFile) {
  unsigned width, height, r, g, b, x, y;

  /* Read size parameters */
  if ( fscanf(fp, "%d %d\n", &width, &height) != 2 )
    throw std::exception(); // "ERROR: input file couldn't be correctly parsed"
      
  /* Render the image */
  png::image< png::rgb_pixel > image(width, height);
  while ( fscanf(fp, "%u %u %u %u %u\n", &x, &y, &r, &g, &b) == 5 ) {
    image[y][x] = png::rgb_pixel(r, g, b);
  }

  image.write(imageFile);
}
