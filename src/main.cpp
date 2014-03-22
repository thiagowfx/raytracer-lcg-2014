#include "main.h"

const char world_output[] = "world_output.txt";
const char image_output[] = "image_output.png";

void build_world();


/* Main */
int main() {
  build_world();
  
  return 0;
}


void build_world() {
  FILE *fp;
  World w;

  /* Set up and execute the Raytracer */
  if ( (fp = fopen(world_output, "w")) != NULL) {
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



void World::build() {

  //////////////////////////////////////////////////
  /* World */
  // vp (ViewPlane)
  background_color = yellow;
  // tracer_ptr (Tracer)
  //////////////////////////////////////////////////
  

  //////////////////////////////////////////////////
  /* View Plane */
  vp.set_hres(400);
  vp.set_vres(400);
  vp.set_pixel_size(0.5);
  vp.set_num_samples(5);
  // vp.set_gamma(1.0);
  // vp.set_show_of_gamut(false);
  //////////////////////////////////////////////////
  
  
  //////////////////////////////////////////////////
  /* Tracer */
  // You may choose between RayCast, MultipleObjects and the dummy Tracer
  // tracer_ptr = new Tracer(this);
  tracer_ptr = new RayCast(this);
  // tracer_ptr = new MultipleObjects(this);
  //////////////////////////////////////////////////


  //////////////////////////////////////////////////
  /* Ambient Light */
  Ambient* ambient_ptr = new Ambient();
  // ambient_ptr->scale_radiance(1.0);
  // ambient_ptr->set_color(red); // default: white
  set_ambient_light(ambient_ptr);
  //////////////////////////////////////////////////


  
  //////////////////////////////////////////////////
  /* Camera */
  Pinhole* pinhole_ptr = new Pinhole();
  pinhole_ptr->set_eye(0, 0, 500); 
  pinhole_ptr->set_lookat(Vector3d::Zero());
  pinhole_ptr->set_view_distance(600.0); // zoom: greater is nearer
  pinhole_ptr->compute_uvw();     
  set_camera(pinhole_ptr);
  //////////////////////////////////////////////////


  //////////////////////////////////////////////////
  /* Directional Light */
  Directional* light_ptr1 = new Directional();
  light_ptr1->set_direction(100, 100, 200);
  light_ptr1->scale_radiance(3.0);
  light_ptr1->set_color(green);
  add_light(light_ptr1);
  //////////////////////////////////////////////////
 

  //////////////////////////////////////////////////
  /* Matte material reflection coefficients - common to all materials */	
  // float ka = 0.25;
  float ka = 0.40;
  float kd = 0.75;
  

  /* Spheres */
  Matte* matte_ptr1 = new Matte;   
  matte_ptr1->set_ka(ka);	
  matte_ptr1->set_kd(kd);
  matte_ptr1->set_cd(yellow);				
  Sphere* sphere_ptr1 = new Sphere(Vector3d(5, 3, 0), 30); 
  sphere_ptr1->set_material(matte_ptr1); 
  sphere_ptr1->set_color(yellow);
  add_object(sphere_ptr1);
	
  Matte* matte_ptr2 = new Matte;
  matte_ptr2->set_ka(ka);	
  matte_ptr2->set_kd(kd);
  matte_ptr2->set_cd(brown);
  Sphere*	sphere_ptr2 = new Sphere(Vector3d(45, -7, -60), 20);
  sphere_ptr2->set_material(matte_ptr2); 
  add_object(sphere_ptr2);
	
  Matte* matte_ptr3 = new Matte;
  matte_ptr3->set_ka(ka);	
  matte_ptr3->set_kd(kd);
  matte_ptr3->set_cd(dark_green);	
  Sphere*	sphere_ptr3 = new Sphere(Vector3d(40, 43, -100), 17); 
  sphere_ptr3->set_material(matte_ptr3); 
  add_object(sphere_ptr3);
	
  Matte* matte_ptr4 = new Matte;
  matte_ptr4->set_ka(ka);	
  matte_ptr4->set_kd(kd);
  matte_ptr4->set_cd(orange);
  Sphere*	sphere_ptr4 = new Sphere(Vector3d(-20, 28, -15), 20); 
  sphere_ptr4->set_material(matte_ptr4); 
  add_object(sphere_ptr4);
	
  Matte* matte_ptr5 = new Matte;
  matte_ptr5->set_ka(ka);	
  matte_ptr5->set_kd(kd);
  matte_ptr5->set_cd(green);
  Sphere*	sphere_ptr5 = new Sphere(Vector3d(-25, -7, -35), 27); 			
  sphere_ptr5->set_material(matte_ptr5); 
  add_object(sphere_ptr5);
	
  Matte* matte_ptr6 = new Matte;
  matte_ptr6->set_ka(ka);	
  matte_ptr6->set_kd(kd);
  matte_ptr6->set_cd(light_green);
  Sphere*	sphere_ptr6 = new Sphere(Vector3d(20, -27, -35), 25); 
  sphere_ptr6->set_material(matte_ptr6); 
  add_object(sphere_ptr6);
	
  Matte* matte_ptr7 = new Matte;
  matte_ptr7->set_ka(ka);	
  matte_ptr7->set_kd(kd);
  matte_ptr7->set_cd(green);
  Sphere*	sphere_ptr7 = new Sphere(Vector3d(35, 18, -35), 22); 
  sphere_ptr7->set_material(matte_ptr7); 
  add_object(sphere_ptr7);
	
  Matte* matte_ptr8 = new Matte;
  matte_ptr8->set_ka(ka);	
  matte_ptr8->set_kd(kd);
  matte_ptr8->set_cd(brown);
  Sphere*	sphere_ptr8 = new Sphere(Vector3d(-57, -17, -50), 15);  
  sphere_ptr8->set_material(matte_ptr8); 
  add_object(sphere_ptr8);
	
  Matte* matte_ptr9 = new Matte;
  matte_ptr9->set_ka(ka);	
  matte_ptr9->set_kd(kd);
  matte_ptr9->set_cd(light_green);
  Sphere*	sphere_ptr9 = new Sphere(Vector3d(-47, 16, -80), 23); 
  sphere_ptr9->set_material(matte_ptr9); 
  add_object(sphere_ptr9);
		
  Matte* matte_ptr10 = new Matte;
  matte_ptr10->set_ka(ka);	
  matte_ptr10->set_kd(kd);
  matte_ptr10->set_cd(dark_green);	
  Sphere*	sphere_ptr10 = new Sphere(Vector3d(-15, -32, -60), 22); 
  sphere_ptr10->set_material(matte_ptr10); 
  add_object(sphere_ptr10);
	
  Matte* matte_ptr11 = new Matte;
  matte_ptr11->set_ka(ka);	
  matte_ptr11->set_kd(kd);
  matte_ptr11->set_cd(dark_yellow);
  Sphere*	sphere_ptr11 = new Sphere(Vector3d(-35, -37, -80), 22); 
  sphere_ptr11->set_material(matte_ptr11); 
  add_object(sphere_ptr11);
	
  Matte* matte_ptr12 = new Matte;
  matte_ptr12->set_ka(ka);	
  matte_ptr12->set_kd(kd);
  matte_ptr12->set_cd(dark_yellow);
  Sphere*	sphere_ptr12 = new Sphere(Vector3d(10, 43, -80), 22); 
  sphere_ptr12->set_material(matte_ptr12); 
  add_object(sphere_ptr12);
	
  Matte* matte_ptr13 = new Matte;
  matte_ptr13->set_ka(ka);	
  matte_ptr13->set_kd(kd);
  matte_ptr13->set_cd(dark_yellow);		
  Sphere*	sphere_ptr13 = new Sphere(Vector3d(30, -7, -80), 10); 
  sphere_ptr13->set_material(matte_ptr13);
  add_object(sphere_ptr13); 
	
  Matte* matte_ptr14 = new Matte;
  matte_ptr14->set_ka(ka);	
  matte_ptr14->set_kd(kd);
  matte_ptr14->set_cd(dark_green);	
  Sphere*	sphere_ptr14 = new Sphere(Vector3d(-40, 48, -110), 18); 
  sphere_ptr14->set_material(matte_ptr14); 
  add_object(sphere_ptr14);
	
  Matte* matte_ptr15 = new Matte;
  matte_ptr15->set_ka(ka);	
  matte_ptr15->set_kd(kd);
  matte_ptr15->set_cd(brown);	
  Sphere*	sphere_ptr15 = new Sphere(Vector3d(-10, 53, -120), 18); 
  sphere_ptr15->set_material(matte_ptr15); 
  add_object(sphere_ptr15);
	
  Matte* matte_ptr16 = new Matte;
  matte_ptr16->set_ka(ka);	
  matte_ptr16->set_kd(kd);
  matte_ptr16->set_cd(light_purple);
  Sphere*	sphere_ptr16 = new Sphere(Vector3d(-55, -52, -100), 10); 
  sphere_ptr16->set_material(matte_ptr16); 
  add_object(sphere_ptr16);
	
  Matte* matte_ptr17 = new Matte;
  matte_ptr17->set_ka(ka);	
  matte_ptr17->set_kd(kd);
  matte_ptr17->set_cd(brown);
  Sphere*	sphere_ptr17 = new Sphere(Vector3d(5, -52, -100), 15); 		
  sphere_ptr17->set_material(matte_ptr17); 
  add_object(sphere_ptr17);
	
  Matte* matte_ptr18 = new Matte;
  matte_ptr18->set_ka(ka);	
  matte_ptr18->set_kd(kd);
  matte_ptr18->set_cd(dark_purple);
  Sphere*	sphere_ptr18 = new Sphere(Vector3d(-20, -57, -120), 15); 
  sphere_ptr18->set_material(matte_ptr18); 
  add_object(sphere_ptr18);
	
  Matte* matte_ptr19 = new Matte;
  matte_ptr19->set_ka(ka);	
  matte_ptr19->set_kd(kd);
  matte_ptr19->set_cd(dark_green);
  Sphere*	sphere_ptr19 = new Sphere(Vector3d(55, -27, -100), 17); 
  sphere_ptr19->set_material(matte_ptr19); 
  add_object(sphere_ptr19);

  Matte* matte_ptr20 = new Matte;
  matte_ptr20->set_ka(ka);	
  matte_ptr20->set_kd(kd);
  matte_ptr20->set_cd(brown);
  Sphere*	sphere_ptr20 = new Sphere(Vector3d(50, -47, -120), 15); 
  sphere_ptr20->set_material(matte_ptr20); 
  add_object(sphere_ptr20);
	 
  Matte* matte_ptr21 = new Matte;
  matte_ptr21->set_ka(ka);	
  matte_ptr21->set_kd(kd);
  matte_ptr21->set_cd(light_purple); 	
  Sphere*	sphere_ptr21 = new Sphere(Vector3d(70, -42, -150), 10); 
  sphere_ptr21->set_material(matte_ptr21); 
  add_object(sphere_ptr21);
	
  Matte* matte_ptr22 = new Matte;
  matte_ptr22->set_ka(ka);	
  matte_ptr22->set_kd(kd);
  matte_ptr22->set_cd(light_purple);
  Sphere*	sphere_ptr22 = new Sphere(Vector3d(5, 73, -130), 12); 
  sphere_ptr22->set_material(matte_ptr22); 
  add_object(sphere_ptr22);
	
  Matte* matte_ptr23 = new Matte;
  matte_ptr23->set_ka(ka);	
  matte_ptr23->set_kd(kd);
  matte_ptr23->set_cd(dark_purple);
  Sphere*	sphere_ptr23 = new Sphere(Vector3d(66, 21, -130), 13); 			
  sphere_ptr23->set_material(matte_ptr23); 
  add_object(sphere_ptr23);	
	
  Matte* matte_ptr24 = new Matte;
  matte_ptr24->set_ka(ka);	
  matte_ptr24->set_kd(kd);
  matte_ptr24->set_cd(light_purple);  
  Sphere*	sphere_ptr24 = new Sphere(Vector3d(72, -12, -140), 12); 
  sphere_ptr24->set_material(matte_ptr24); 
  add_object(sphere_ptr24);
	
  Matte* matte_ptr25 = new Matte;
  matte_ptr25->set_ka(ka);	
  matte_ptr25->set_kd(kd);
  matte_ptr25->set_cd(green);
  Sphere*	sphere_ptr25 = new Sphere(Vector3d(64, 5, -160), 11); 			
  sphere_ptr25->set_material(matte_ptr25); 
  add_object(sphere_ptr25);
	  
  Matte* matte_ptr26 = new Matte;
  matte_ptr26->set_ka(ka);	
  matte_ptr26->set_kd(kd);
  matte_ptr26->set_cd(light_purple);
  Sphere*	sphere_ptr26 = new Sphere(Vector3d(55, 38, -160), 12); 		
  sphere_ptr26->set_material(matte_ptr26); 
  add_object(sphere_ptr26);
	
  Matte* matte_ptr27 = new Matte;
  matte_ptr27->set_ka(ka);	
  matte_ptr27->set_kd(kd);
  matte_ptr27->set_cd(light_purple);
  Sphere*	sphere_ptr27 = new Sphere(Vector3d(-73, -2, -160), 12); 		
  sphere_ptr27->set_material(matte_ptr27); 
  add_object(sphere_ptr27);
	 
  Matte* matte_ptr28 = new Matte;
  matte_ptr28->set_ka(ka);	
  matte_ptr28->set_kd(kd);
  matte_ptr28->set_cd(dark_purple);
  Sphere*	sphere_ptr28 = new Sphere(Vector3d(30, -62, -140), 15); 
  sphere_ptr28->set_material(matte_ptr28); 
  add_object(sphere_ptr28);
	
  Matte* matte_ptr29 = new Matte;
  matte_ptr29->set_ka(ka);	
  matte_ptr29->set_kd(kd);
  matte_ptr29->set_cd(dark_purple);
  Sphere*	sphere_ptr29 = new Sphere(Vector3d(25, 63, -140), 15); 
  sphere_ptr29->set_material(matte_ptr29); 
  add_object(sphere_ptr29);
	
  Matte* matte_ptr30 = new Matte;
  matte_ptr30->set_ka(ka);	
  matte_ptr30->set_kd(kd);
  matte_ptr30->set_cd(dark_purple);
  Sphere*	sphere_ptr30 = new Sphere(Vector3d(-60, 46, -140), 15);  
  sphere_ptr30->set_material(matte_ptr30); 
  add_object(sphere_ptr30);
	
  Matte* matte_ptr31 = new Matte;
  matte_ptr31->set_ka(ka);	
  matte_ptr31->set_kd(kd);
  matte_ptr31->set_cd(light_purple);
  Sphere*	sphere_ptr31 = new Sphere(Vector3d(-30, 68, -130), 12); 
  sphere_ptr31->set_material(matte_ptr31); 
  add_object(sphere_ptr31);
	
  Matte* matte_ptr32 = new Matte;
  matte_ptr32->set_ka(ka);	
  matte_ptr32->set_kd(kd);
  matte_ptr32->set_cd(green);
  Sphere*	sphere_ptr32 = new Sphere(Vector3d(58, 56, -180), 11);   
  sphere_ptr32->set_material(matte_ptr32); 
  add_object(sphere_ptr32);
	
  Matte* matte_ptr33 = new Matte;
  matte_ptr33->set_ka(ka);	
  matte_ptr33->set_kd(kd);
  matte_ptr33->set_cd(green);
  Sphere*	sphere_ptr33 = new Sphere(Vector3d(-63, -39, -180), 11); 
  sphere_ptr33->set_material(matte_ptr33); 
  add_object(sphere_ptr33);
	
  Matte* matte_ptr34 = new Matte;
  matte_ptr34->set_ka(ka);	
  matte_ptr34->set_kd(kd);
  matte_ptr34->set_cd(light_purple);
  Sphere*	sphere_ptr34 = new Sphere(Vector3d(46, 68, -200), 10); 	
  sphere_ptr34->set_material(matte_ptr34); 
  add_object(sphere_ptr34);
	
  Matte* matte_ptr35 = new Matte;
  matte_ptr35->set_ka(ka);	
  matte_ptr35->set_kd(kd);
  matte_ptr35->set_cd(light_purple);
  Sphere*	sphere_ptr35 = new Sphere(Vector3d(-3, -72, -130), 12); 
  sphere_ptr35->set_material(matte_ptr35); 
  add_object(sphere_ptr35);
	
  /* Vertical plane */
  Matte* matte_ptr36 = new Matte;
  matte_ptr36->set_ka(ka);	
  matte_ptr36->set_kd(kd);
  matte_ptr36->set_cd(grey);
  
  Plane* plane_ptr = new Plane(Vector3d(0, 0, -150), Vector3d(0, 0, 1));
  plane_ptr->set_material(matte_ptr36);
  plane_ptr->set_color(blue);
  add_object (plane_ptr);
}
