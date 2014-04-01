#include "main.h"

const char image_file[] = "raytraced_image.png";
const float ka = 0.30;
const float kd = 0.75;

void build_base_world(World& w);
void build_primitives(World& w);
void build_single_sphere(World& w);
void build_shaded_spheres(World& w);


int main() {
  World w;
  build_base_world(w);

  build_single_sphere(w);
  // build_shaded_spheres(w);

  puts("INFO: BEGIN build_primitives");
  build_primitives(w);
  puts("INFO: END build_primitives");

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
  w.vp.set_hres(450);
  w.vp.set_vres(450);
  w.vp.set_pixel_size(0.6);
  w.vp.set_samples(5);
  w.tracer_ptr = new MultipleObjects(&w);
  // w.tracer_ptr = new RayCast(&w);
  Ambient* ambient_ptr = new Ambient();
  ambient_ptr->scale_radiance(1.0);
  w.set_ambient_light(ambient_ptr);
  Pinhole* pinhole_ptr = new Pinhole();
  pinhole_ptr->set_eye(Vector3d(2, -1.5, 1));
  pinhole_ptr->set_lookat(Vector3d::Zero());
  pinhole_ptr->set_view_distance(75.0); // zoom: greater is nearer
  pinhole_ptr->compute_uvw();
  // FishEye* fisheye_ptr = new FishEye();
  // fisheye_ptr->set_fov(35);
  w.set_camera(pinhole_ptr);
}


void build_primitives(World& w) {
  // TODO remover newPoints?
  // glwidget.cpp -> loadMesh2()
  // primitive.h -> hit (rayIntersection)

  /* global */
  char filename[] = "/home/thiago/workbench/RaytracerProject/projects/SHAPES2";
  vector<Primitive*> primitives;
  vector<Shape*> candidates;
  vector<Element> newPoints;

  double epsilon = 0.3;
  double alpha = 40;
  double tao = 50;
  double pt = 0.99;
  int k = 3;
  int r = 100;
  int maxElements = 30;
  int maxLevel = 10;
  int option = -1;
  int option2 = -1;
  PCShapeDetection littlePCSD;

  /* loadMesh2 */
  epsilon = 0.05;
  alpha = 10;

  if (filename == 0) {
    puts("ERROR: No primitives file set.");
  }

  ifstream data(filename);
  double x,y,z;
  double nx, ny, nz;
  vector<Point> points;
  vector<Point> normals;

  while (data >> x >> y >> z) {
    Point newPoint(x,y,z);
    data >> nx >> ny >> nz;
    Point newNormal(nx, ny, nz);
    points.push_back(newPoint);
    normals.push_back(newNormal);
    Element newElement;
    newElement.location = newPoint;
    newElement.normal = newNormal;
    newPoints.push_back(newElement);
  }

  littlePCSD.set(points, normals, k, epsilon, tao, pt, alpha,r, maxElements,maxLevel);
  littlePCSD.detect(true); // let this be TRUE
  primitives = littlePCSD.getPrimitives();
  candidates = littlePCSD.getCandidates();

  cout << "Número de primitivas: " << primitives.size() << endl;
  cout << "Número de candidatos: " << candidates.size() << endl;

  vector<RGBColor> colors;
  colors.push_back(grey);
  colors.push_back(blue);
  colors.push_back(brown);
  colors.push_back(dark_purple);
  colors.push_back(dark_yellow);
  colors.push_back(green);
  colors.push_back(light_green);
  colors.push_back(light_purple);
  colors.push_back(dark_green);
  colors.push_back(orange);
  colors.push_back(red);
  colors.push_back(white);
  colors.push_back(yellow);

  PrimitivaDaniel* pd;
  Matte* matte_ptr;
  
  for (unsigned int i = 0; i < primitives.size(); ++i) {
    pd = new PrimitivaDaniel(primitives[i]);
    matte_ptr = new Matte;
    matte_ptr->set_ka(ka);
    matte_ptr->set_kd(kd);
    matte_ptr->set_cd(colors[i % colors.size()]);
    pd->set_color(colors[i % colors.size()]);
    pd->set_material(matte_ptr);
    w.add_object(pd);
  }
}


void build_single_sphere(World& w) {
  Matte* matte_ptr1 = new Matte();
  matte_ptr1->set_ka(ka);
  matte_ptr1->set_kd(kd);
  matte_ptr1->set_cd(orange);
  RaytracerSphere* sphere_ptr1 = new RaytracerSphere(Vector3d(0, 0, 0), 1);
  sphere_ptr1->set_color(orange);
  sphere_ptr1->set_material(matte_ptr1);
  w.add_object(sphere_ptr1);
}


void build_shaded_spheres(World &w) {
  Directional* light_ptr1 = new Directional();
  light_ptr1->set_direction(Vector3d(100, 100, 200));
  light_ptr1->scale_radiance(3.0);
  light_ptr1->set_color(green);
  w.add_light(light_ptr1);

  /* RaytracerSpheres */
  Matte* matte_ptr1 = new Matte;
  matte_ptr1->set_ka(ka);
  matte_ptr1->set_kd(kd);
  matte_ptr1->set_cd(yellow);
  RaytracerSphere* sphere_ptr1 = new RaytracerSphere(Vector3d(5, 3, 0), 30);
  sphere_ptr1->set_material(matte_ptr1);
  sphere_ptr1->set_color(yellow);
  w.add_object(sphere_ptr1);

  Matte* matte_ptr2 = new Matte;
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
