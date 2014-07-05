#ifndef _CAMERA_MINE_
#define _CAMERA_MINE_

#include <Eigen/Dense>
using Eigen::Vector2d;
using Eigen::Vector3d;

namespace Raytracer {
  class World;
  class Camera {
  public:
    /** Constructor. */
    Camera();

    /** Copy constructor. */
    Camera(const Camera& camera);
    
    virtual Camera* clone() const = 0;
    virtual ~Camera();
    virtual void render_scene(const World* w, const char* image_file) = 0;
    void set_eye(const Vector3d&);
    void set_lookat(const Vector3d&);
    void set_up_vector(const Vector3d&);
    void set_exposure_time(double exposure);
    void set_zoom(double zoom);
    void set_view_distance(double d);
    Vector3d get_eye() const;
    double get_view_distance() const;
  protected:
    /** Camera position. */
    Vector3d eye = Vector3d(0.0, 0.0, 250.0);

    /** Point where the camera is looking at. */
    Vector3d lookat = Vector3d::Zero();

    /** Up vector. */
    Vector3d up = Vector3d(0.0, 1.0, 0.0);

    /** Orthonormal basis vector. */
    Vector3d u = Vector3d(1.0, 0.0, 0.0);

    /** Orthonormal basis vector. */
    Vector3d v = Vector3d(0.0, 1.0, 0.0);

    /** Orthonormal basis vector. */
    Vector3d w = Vector3d(0.0, 0.0, 1.0);

    /** Exposure time. */
    double exposure_time = 1.0;

    /** Zoom factor. More is nearer. */
    double zoom = 1.0;

    /** View plane distance. */
    double d = 250.0;

    /** Compute orthonormal basis vectors. Should be called every time when eye, lookat or up vectors are changed. */
    void compute_uvw();
  };


  inline void Camera::set_eye(const Vector3d& eye) {
    this->eye = eye;
    compute_uvw();
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


  inline Vector3d Camera::get_eye() const {
    return eye;
  }


  inline double Camera::get_view_distance() const {
    return d;
  }


  inline void Camera::set_zoom(double zoom) {
    this->zoom = zoom;
  }


  inline void Camera::set_view_distance(double d) {
    this->d = d;
  }
}

#endif // _CAMERA_MINE_
