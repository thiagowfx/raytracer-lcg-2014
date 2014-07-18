#ifndef _CAMERA_MINE_
#define _CAMERA_MINE_

#include <ctime>
#include "World.h"
#include <Eigen/Dense>
using Eigen::Vector2d;
using Eigen::Vector3d;

namespace Raytracer {
  class World;
  /** @brief A pinhole camera, with perspective viewing. */
  class Camera {
  public:
    Camera();
    Camera(const Camera& camera);
    ~Camera();
    Camera* clone() const;

    /* Setters. */
    void set_eye_position(const Vector3d&);
    void set_lookat(const Vector3d&);
    void set_up_vector(const Vector3d&);
    void set_exposure_time(double);
    void set_zoom(double);
    void set_distance(double);

    /* Getters. */
    Vector3d get_eye_position() const;
    Vector3d get_lookat() const;
    double get_distance() const;
    double get_zoom() const;

    /** Render an image from world elements, returns the time it took in milliseconds. */
    unsigned render_scene(const World*, const char* image_file);

  private:
    /** Camera position. */
    Vector3d eye = Vector3d(100.0, 100.0, 100.0);

    /** Point where the camera is looking at. */
    Vector3d lookat = Vector3d::Zero();

    /** Exposure time. */
    double exposure_time = 1.0;

    /** Zoom factor. More is nearer. */
    double zoom = 1.0;

    /** Distance between the viewplane and the camera eye. More is nearer. */
    double distance = 100.0;

    /** Up vector -- in y direction. */
    Vector3d up = Vector3d(0.0, 1.0, 0.0);

    /** Orthonormal basis vector. */
    Vector3d u = Vector3d(1.0, 0.0, 0.0);

    /** Orthonormal basis vector. */
    Vector3d v = Vector3d(0.0, 1.0, 0.0);

    /** Orthonormal basis vector. */
    Vector3d w = Vector3d(0.0, 0.0, 1.0);

    /** Return a vector which has eye and p as its ends. */
    Vector3d get_direction(const Vector2d&) const;

    /** Compute u, v and w vectors. They depend upon eye, up and lookat. */
    void compute_uvw();
  };

  
  inline void Camera::set_eye_position(const Vector3d& eye) {
    this->eye = eye;
    compute_uvw();
  }


  inline Vector3d Camera::get_lookat() const {
    return this->lookat;
  }


  inline void Camera::set_lookat(const Vector3d& p) {
    lookat = p;
    compute_uvw();
  }


  inline void Camera::set_up_vector(const Vector3d& u) {
    up = u;
    compute_uvw();
  }


  inline void Camera::set_exposure_time(double exposure_time) {
    this->exposure_time = exposure_time;
  }


  inline Vector3d Camera::get_eye_position() const {
    return eye;
  }


  inline double Camera::get_distance() const {
    return this->distance;
  }


  inline double Camera::get_zoom() const {
    return this->zoom;
  }


  inline void Camera::set_zoom(double zoom) {
    this->zoom = zoom;
  }


  inline void Camera::set_distance(double distance) {
    this->distance = distance;
  }
}

#endif // _CAMERA_MINE_
