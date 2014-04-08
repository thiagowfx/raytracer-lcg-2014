#include "main.h"

const char image_file[] = "raytraced_image.png";
const float ka = 0.25;
const float kd = 0.75;
const float ks = 0.12;
const float expi = 20;

void build_base_world(World& w);
void build_single_sphere(World& w);
void build_shaded_spheres(World& w);

int main() {
  World w;
  build_base_world(w);

  int num_samples = 1;

  w.vp.set_hres(400);
  w.vp.set_vres(400);
  w.vp.set_samples(num_samples);

  w.background_color = black;
  w.tracer_ptr = new RayCast(&w);

  Pinhole* camera_ptr = new Pinhole;
  camera_ptr->set_eye(Vector3d(0, 0, 250));
  camera_ptr->set_lookat(Vector3d::Zero());
  camera_ptr->set_view_distance(200);   // for Figure 8.16(a)
  //    camera_ptr->set_view_distance(450);     // for Figure 8.16(b)
  //    camera_ptr->set_view_distance(1000);    // for Figure 8.16(c)
  camera_ptr->compute_uvw();
  w.set_camera(camera_ptr);


  PointLight* light_ptr1 = new PointLight;
  light_ptr1->set_location(Vector3d(50, 150, 200));
  light_ptr1->set_location(Vector3d(0, 0, -250));
  light_ptr1->scale_radiance(6.0);
  // light_ptr1->set_shadows(true);
  w.add_light(light_ptr1);


  Phong* phong_ptr1 = new Phong;
  phong_ptr1->set_ka(0.5);
  phong_ptr1->set_kd(0.4);
  phong_ptr1->set_cd(yellow);
  phong_ptr1->set_ks(0.05);
  phong_ptr1->set_exp(25);

  Reflective* reflexive_ptr1 = new Reflective;
  reflexive_ptr1->set_kr(1.0);
  reflexive_ptr1->set_cd(red);

  RaytracerSphere*   sphere_ptr1 = new RaytracerSphere(Vector3d(-45, 45, 40), 50);
  sphere_ptr1->set_color(red);
  sphere_ptr1->set_material(phong_ptr1);
  // sphere_ptr1->set_material(reflexive_ptr1);
  w.add_object(sphere_ptr1);

  Phong*    phong_ptr2 = new Phong;
  phong_ptr2->set_ka(0.25);
  phong_ptr2->set_kd(0.5);
  phong_ptr2->set_cd(RGBColor(0, 0.5, 0.5));     // cyan
  phong_ptr2->set_ks(0.05);
  phong_ptr2->set_exp(50);

  Triangle* triangle_ptr1 = new Triangle(Vector3d(-110, -85, 80), Vector3d(120, 10, 20), Vector3d(-40, 50, -30));
  triangle_ptr1->set_material(phong_ptr2);
  triangle_ptr1->set_material(reflexive_ptr1);
  w.add_object(triangle_ptr1);


  // build_shaded_spheres(w);
  // build_single_sphere(w);

  if (w.tracer_ptr == NULL) {
    puts("ERROR: No world tracer set.");
    exit(1);
  }

  puts("INFO: BEGIN render_scene");
  w.camera_ptr->render_scene(w, image_file);
  puts("INFO: END render_scene");

  return 0;
}


void build_base_world(World& w) {
  w.background_color = black;
  w.vp.set_hres(500);
  w.vp.set_vres(500);
  w.vp.set_pixel_size(1.0);
  w.vp.set_samples(4);
  w.vp.set_max_depth(3);

  w.tracer_ptr = new MultipleObjects(&w);
  // w.tracer_ptr = new RayCast(&w);

  Ambient* ambient_ptr = new Ambient();
  ambient_ptr->scale_radiance(1.0);
  w.set_ambient_light(ambient_ptr);

  Pinhole* pinhole_ptr = new Pinhole();
  // pinhole_ptr->set_eye(Vector3d(2, -1.5, 1));
  pinhole_ptr->set_eye(Vector3d(0, 0, 100));
  pinhole_ptr->set_lookat(Vector3d::Zero());
  pinhole_ptr->set_view_distance(75.0); // zoom: greater is nearer
  pinhole_ptr->set_zoom(1.0);
  pinhole_ptr->compute_uvw();
  // w.set_camera(pinhole_ptr);

  Orthographic* ortographic_ptr = new Orthographic();
  w.set_camera(ortographic_ptr);

  // PointLight* light_ptr = new PointLight();
  // light_ptr->set_location(Vector3d(100, 100, 200));
  // light_ptr->scale_radiance(2.0);
  // w.add_light(light_ptr);

  // Directional* light_ptr1 = new Directional();
  // light_ptr1->set_direction(Vector3d(2, -1.5, 1));
  // light_ptr1->set_direction(Vector3d(1.0, 1.0, 2.0));
  // light_ptr1->scale_radiance(2.0);
  // w.add_light(light_ptr1);
}


void build_single_sphere(World& w) {
  Phong* phong_ptr1 = new Phong();
  phong_ptr1->set_ka(ka);
  phong_ptr1->set_kd(kd);
  phong_ptr1->set_ks(ks);
  phong_ptr1->set_exp(expi);
  phong_ptr1->set_cd(yellow);

  Matte* matte_ptr1 = new Matte();
  matte_ptr1->set_ka(ka);
  matte_ptr1->set_kd(kd);
  matte_ptr1->set_cd(yellow);

  RaytracerSphere* sphere_ptr1 = new RaytracerSphere(Vector3d(0, 0, 0), 1);
  sphere_ptr1->set_color(yellow);
  sphere_ptr1->set_material(matte_ptr1);
  w.add_object(sphere_ptr1);
}


void build_shaded_spheres(World &w) {
  Phong* phong_ptr1 = new Phong();
  phong_ptr1->set_ka(ka);
  phong_ptr1->set_kd(kd);
  phong_ptr1->set_ks(ks);
  phong_ptr1->set_exp(expi);
  phong_ptr1->set_cd(yellow);

  Matte* matte_ptr1 = new Matte();
  matte_ptr1->set_ka(ka);
  matte_ptr1->set_kd(kd);
  matte_ptr1->set_cd(yellow);

  RaytracerSphere* sphere_ptr1 = new RaytracerSphere(Vector3d(5, 3, 0), 30);
  sphere_ptr1->set_color(yellow);
  sphere_ptr1->set_material(matte_ptr1);
  w.add_object(sphere_ptr1);

  Phong* phong_ptr2 = new Phong();
  phong_ptr2->set_ka(ka);
  phong_ptr2->set_kd(kd);
  phong_ptr2->set_ks(ks);
  phong_ptr2->set_exp(expi);
  phong_ptr2->set_cd(brown);

  Matte* matte_ptr2 = new Matte();
  matte_ptr2->set_ka(ka);
  matte_ptr2->set_kd(kd);
  matte_ptr2->set_cd(brown);

  RaytracerSphere*   sphere_ptr2 = new RaytracerSphere(Vector3d(45, -7, -60), 20);
  sphere_ptr2->set_material(matte_ptr2);
  sphere_ptr2->set_color(brown);
  w.add_object(sphere_ptr2);

  Matte* matte_ptr3 = new Matte;
  matte_ptr3->set_ka(ka);
  matte_ptr3->set_kd(kd);
  matte_ptr3->set_cd(dark_green);
  RaytracerSphere*   sphere_ptr3 = new RaytracerSphere(Vector3d(40, 43, -100), 17);
  sphere_ptr3->set_color(dark_green);
  sphere_ptr3->set_material(matte_ptr3);
  w.add_object(sphere_ptr3);

  Matte* matte_ptr4 = new Matte;
  matte_ptr4->set_ka(ka);
  matte_ptr4->set_kd(kd);
  matte_ptr4->set_cd(orange);
  RaytracerSphere*   sphere_ptr4 = new RaytracerSphere(Vector3d(-20, 28, -15), 20);
  sphere_ptr4->set_color(orange);
  sphere_ptr4->set_material(matte_ptr4);
  w.add_object(sphere_ptr4);

  Matte* matte_ptr5 = new Matte;
  matte_ptr5->set_ka(ka);
  matte_ptr5->set_kd(kd);
  matte_ptr5->set_cd(green);
  RaytracerSphere*   sphere_ptr5 = new RaytracerSphere(Vector3d(-25, -7, -35), 27);
  sphere_ptr5->set_color(green);
  sphere_ptr5->set_material(matte_ptr5);
  w.add_object(sphere_ptr5);

  Matte* matte_ptr6 = new Matte;
  matte_ptr6->set_ka(ka);
  matte_ptr6->set_kd(kd);
  matte_ptr6->set_cd(light_green);
  RaytracerSphere*   sphere_ptr6 = new RaytracerSphere(Vector3d(20, -27, -35), 25);
  sphere_ptr6->set_color(light_green);
  sphere_ptr6->set_material(matte_ptr6);
  w.add_object(sphere_ptr6);

  Matte* matte_ptr7 = new Matte;
  matte_ptr7->set_ka(ka);
  matte_ptr7->set_kd(kd);
  matte_ptr7->set_cd(green);
  RaytracerSphere*   sphere_ptr7 = new RaytracerSphere(Vector3d(35, 18, -35), 22);
  sphere_ptr7->set_color(green);
  sphere_ptr7->set_material(matte_ptr7);
  w.add_object(sphere_ptr7);

  Matte* matte_ptr8 = new Matte;
  matte_ptr8->set_ka(ka);
  matte_ptr8->set_kd(kd);
  matte_ptr8->set_cd(brown);
  RaytracerSphere*   sphere_ptr8 = new RaytracerSphere(Vector3d(-57, -17, -50), 15);
  sphere_ptr8->set_color(brown);
  sphere_ptr8->set_material(matte_ptr8);
  w.add_object(sphere_ptr8);

  Matte* matte_ptr9 = new Matte;
  matte_ptr9->set_ka(ka);
  matte_ptr9->set_kd(kd);
  matte_ptr9->set_cd(light_green);
  RaytracerSphere*   sphere_ptr9 = new RaytracerSphere(Vector3d(-47, 16, -80), 23);
  sphere_ptr9->set_color(light_green);
  sphere_ptr9->set_material(matte_ptr9);
  w.add_object(sphere_ptr9);

  Matte* matte_ptr10 = new Matte;
  matte_ptr10->set_ka(ka);
  matte_ptr10->set_kd(kd);
  matte_ptr10->set_cd(dark_green);
  RaytracerSphere*   sphere_ptr10 = new RaytracerSphere(Vector3d(-15, -32, -60), 22);
  sphere_ptr10->set_color(dark_green);
  sphere_ptr10->set_material(matte_ptr10);
  w.add_object(sphere_ptr10);

  Matte* matte_ptr11 = new Matte;
  matte_ptr11->set_ka(ka);
  matte_ptr11->set_kd(kd);
  matte_ptr11->set_cd(dark_yellow);
  RaytracerSphere*   sphere_ptr11 = new RaytracerSphere(Vector3d(-35, -37, -80), 22);
  sphere_ptr11->set_color(dark_yellow);
  sphere_ptr11->set_material(matte_ptr11);
  w.add_object(sphere_ptr11);

  Matte* matte_ptr12 = new Matte;
  matte_ptr12->set_ka(ka);
  matte_ptr12->set_kd(kd);
  matte_ptr12->set_cd(dark_yellow);
  RaytracerSphere*   sphere_ptr12 = new RaytracerSphere(Vector3d(10, 43, -80), 22);
  sphere_ptr12->set_color(dark_yellow);
  sphere_ptr12->set_material(matte_ptr12);
  w.add_object(sphere_ptr12);

  Matte* matte_ptr13 = new Matte;
  matte_ptr13->set_ka(ka);
  matte_ptr13->set_kd(kd);
  matte_ptr13->set_cd(dark_yellow);
  RaytracerSphere*   sphere_ptr13 = new RaytracerSphere(Vector3d(30, -7, -80), 10);
  sphere_ptr13->set_color(dark_yellow);
  sphere_ptr13->set_material(matte_ptr13);
  w.add_object(sphere_ptr13);

  Matte* matte_ptr14 = new Matte;
  matte_ptr14->set_ka(ka);
  matte_ptr14->set_kd(kd);
  matte_ptr14->set_cd(dark_green);
  RaytracerSphere*   sphere_ptr14 = new RaytracerSphere(Vector3d(-40, 48, -110), 18);
  sphere_ptr14->set_color(dark_green);
  sphere_ptr14->set_material(matte_ptr14);
  w.add_object(sphere_ptr14);

  Matte* matte_ptr15 = new Matte;
  matte_ptr15->set_ka(ka);
  matte_ptr15->set_kd(kd);
  matte_ptr15->set_cd(brown);
  RaytracerSphere*   sphere_ptr15 = new RaytracerSphere(Vector3d(-10, 53, -120), 18);
  sphere_ptr15->set_color(brown);
  sphere_ptr15->set_material(matte_ptr15);
  w.add_object(sphere_ptr15);

  Matte* matte_ptr16 = new Matte;
  matte_ptr16->set_ka(ka);
  matte_ptr16->set_kd(kd);
  matte_ptr16->set_cd(light_purple);
  RaytracerSphere*   sphere_ptr16 = new RaytracerSphere(Vector3d(-55, -52, -100), 10);
  sphere_ptr16->set_color(light_purple);
  sphere_ptr16->set_material(matte_ptr16);
  w.add_object(sphere_ptr16);

  Matte* matte_ptr17 = new Matte;
  matte_ptr17->set_ka(ka);
  matte_ptr17->set_kd(kd);
  matte_ptr17->set_cd(brown);
  RaytracerSphere*   sphere_ptr17 = new RaytracerSphere(Vector3d(5, -52, -100), 15);
  sphere_ptr17->set_color(brown);
  sphere_ptr17->set_material(matte_ptr17);
  w.add_object(sphere_ptr17);

  Matte* matte_ptr18 = new Matte;
  matte_ptr18->set_ka(ka);
  matte_ptr18->set_kd(kd);
  matte_ptr18->set_cd(dark_purple);
  RaytracerSphere*   sphere_ptr18 = new RaytracerSphere(Vector3d(-20, -57, -120), 15);
  sphere_ptr18->set_color(dark_purple);
  sphere_ptr18->set_material(matte_ptr18);
  w.add_object(sphere_ptr18);

  Matte* matte_ptr19 = new Matte;
  matte_ptr19->set_ka(ka);
  matte_ptr19->set_kd(kd);
  matte_ptr19->set_cd(dark_green);
  RaytracerSphere*   sphere_ptr19 = new RaytracerSphere(Vector3d(55, -27, -100), 17);
  sphere_ptr19->set_color(dark_green);
  sphere_ptr19->set_material(matte_ptr19);
  w.add_object(sphere_ptr19);

  Matte* matte_ptr20 = new Matte;
  matte_ptr20->set_ka(ka);
  matte_ptr20->set_kd(kd);
  matte_ptr20->set_cd(brown);
  RaytracerSphere*   sphere_ptr20 = new RaytracerSphere(Vector3d(50, -47, -120), 15);
  sphere_ptr20->set_color(brown);
  sphere_ptr20->set_material(matte_ptr20);
  w.add_object(sphere_ptr20);

  Matte* matte_ptr21 = new Matte;
  matte_ptr21->set_ka(ka);
  matte_ptr21->set_kd(kd);
  matte_ptr21->set_cd(light_purple);
  RaytracerSphere*   sphere_ptr21 = new RaytracerSphere(Vector3d(70, -42, -150), 10);
  sphere_ptr21->set_color(light_purple);
  sphere_ptr21->set_material(matte_ptr21);
  w.add_object(sphere_ptr21);

  Matte* matte_ptr22 = new Matte;
  matte_ptr22->set_ka(ka);
  matte_ptr22->set_kd(kd);
  matte_ptr22->set_cd(light_purple);
  RaytracerSphere*   sphere_ptr22 = new RaytracerSphere(Vector3d(5, 73, -130), 12);
  sphere_ptr22->set_color(light_purple);
  sphere_ptr22->set_material(matte_ptr22);
  w.add_object(sphere_ptr22);

  Matte* matte_ptr23 = new Matte;
  matte_ptr23->set_ka(ka);
  matte_ptr23->set_kd(kd);
  matte_ptr23->set_cd(dark_purple);
  RaytracerSphere*   sphere_ptr23 = new RaytracerSphere(Vector3d(66, 21, -130), 13);
  sphere_ptr23->set_color(dark_purple);
  sphere_ptr23->set_material(matte_ptr23);
  w.add_object(sphere_ptr23);

  Matte* matte_ptr24 = new Matte;
  matte_ptr24->set_ka(ka);
  matte_ptr24->set_kd(kd);
  matte_ptr24->set_cd(light_purple);
  RaytracerSphere*   sphere_ptr24 = new RaytracerSphere(Vector3d(72, -12, -140), 12);
  sphere_ptr24->set_color(light_purple);
  sphere_ptr24->set_material(matte_ptr24);
  w.add_object(sphere_ptr24);

  Matte* matte_ptr25 = new Matte;
  matte_ptr25->set_ka(ka);
  matte_ptr25->set_kd(kd);
  matte_ptr25->set_cd(green);
  RaytracerSphere*   sphere_ptr25 = new RaytracerSphere(Vector3d(64, 5, -160), 11);
  sphere_ptr25->set_color(green);
  sphere_ptr25->set_material(matte_ptr25);
  w.add_object(sphere_ptr25);

  Matte* matte_ptr26 = new Matte;
  matte_ptr26->set_ka(ka);
  matte_ptr26->set_kd(kd);
  matte_ptr26->set_cd(light_purple);
  RaytracerSphere*   sphere_ptr26 = new RaytracerSphere(Vector3d(55, 38, -160), 12);
  sphere_ptr26->set_color(light_purple);
  sphere_ptr26->set_material(matte_ptr26);
  w.add_object(sphere_ptr26);

  Matte* matte_ptr27 = new Matte;
  matte_ptr27->set_ka(ka);
  matte_ptr27->set_kd(kd);
  matte_ptr27->set_cd(light_purple);
  RaytracerSphere*   sphere_ptr27 = new RaytracerSphere(Vector3d(-73, -2, -160), 12);
  sphere_ptr27->set_color(light_purple);
  sphere_ptr27->set_material(matte_ptr27);
  w.add_object(sphere_ptr27);

  Matte* matte_ptr28 = new Matte;
  matte_ptr28->set_ka(ka);
  matte_ptr28->set_kd(kd);
  matte_ptr28->set_cd(dark_purple);
  RaytracerSphere*   sphere_ptr28 = new RaytracerSphere(Vector3d(30, -62, -140), 15);
  sphere_ptr28->set_color(dark_purple);
  sphere_ptr28->set_material(matte_ptr28);
  w.add_object(sphere_ptr28);

  Matte* matte_ptr29 = new Matte;
  matte_ptr29->set_ka(ka);
  matte_ptr29->set_kd(kd);
  matte_ptr29->set_cd(dark_purple);
  RaytracerSphere*   sphere_ptr29 = new RaytracerSphere(Vector3d(25, 63, -140), 15);
  sphere_ptr29->set_color(dark_purple);
  sphere_ptr29->set_material(matte_ptr29);
  w.add_object(sphere_ptr29);

  Matte* matte_ptr30 = new Matte;
  matte_ptr30->set_ka(ka);
  matte_ptr30->set_kd(kd);
  matte_ptr30->set_cd(dark_purple);
  RaytracerSphere*   sphere_ptr30 = new RaytracerSphere(Vector3d(-60, 46, -140), 15);
  sphere_ptr30->set_color(dark_purple);
  sphere_ptr30->set_material(matte_ptr30);
  w.add_object(sphere_ptr30);

  Matte* matte_ptr31 = new Matte;
  matte_ptr31->set_ka(ka);
  matte_ptr31->set_kd(kd);
  matte_ptr31->set_cd(light_purple);
  RaytracerSphere*   sphere_ptr31 = new RaytracerSphere(Vector3d(-30, 68, -130), 12);
  sphere_ptr31->set_color(light_purple);
  sphere_ptr31->set_material(matte_ptr31);
  w.add_object(sphere_ptr31);

  Matte* matte_ptr32 = new Matte;
  matte_ptr32->set_ka(ka);
  matte_ptr32->set_kd(kd);
  matte_ptr32->set_cd(green);
  RaytracerSphere*   sphere_ptr32 = new RaytracerSphere(Vector3d(58, 56, -180), 11);
  sphere_ptr32->set_color(green);
  sphere_ptr32->set_material(matte_ptr32);
  w.add_object(sphere_ptr32);

  Matte* matte_ptr33 = new Matte;
  matte_ptr33->set_ka(ka);
  matte_ptr33->set_kd(kd);
  matte_ptr33->set_cd(green);
  RaytracerSphere*   sphere_ptr33 = new RaytracerSphere(Vector3d(-63, -39, -180), 11);
  sphere_ptr33->set_color(green);
  sphere_ptr33->set_material(matte_ptr33);
  w.add_object(sphere_ptr33);

  Matte* matte_ptr34 = new Matte;
  matte_ptr34->set_ka(ka);
  matte_ptr34->set_kd(kd);
  matte_ptr34->set_cd(light_purple);
  RaytracerSphere*   sphere_ptr34 = new RaytracerSphere(Vector3d(46, 68, -200), 10);
  sphere_ptr34->set_color(light_purple);
  sphere_ptr34->set_material(matte_ptr34);
  w.add_object(sphere_ptr34);

  Matte* matte_ptr35 = new Matte;
  matte_ptr35->set_ka(ka);
  matte_ptr35->set_kd(kd);
  matte_ptr35->set_cd(light_purple);
  RaytracerSphere*   sphere_ptr35 = new RaytracerSphere(Vector3d(-3, -72, -130), 12);
  sphere_ptr35->set_color(light_purple);
  sphere_ptr35->set_material(matte_ptr35);
  w.add_object(sphere_ptr35);

  /* Vertical plane */
  // Matte* matte_ptr36 = new Matte;
  // matte_ptr36->set_ka(ka);
  // matte_ptr36->set_kd(kd);
  // matte_ptr36->set_cd(light_green);
  // RaytracerPlane* plane_ptr = new RaytracerPlane(Vector3d(0, 0, -150), Vector3d(0, 0, 1));
  // plane_ptr->set_material(matte_ptr36);
  // plane_ptr->set_color(light_green);
  // w.add_object (plane_ptr);
}
