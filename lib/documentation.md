# To developers {#mainpage}
## Overview
This project uses [CMake](http://www.cmake.org/) as its management tool. Its directory tree is
organized as follows:

- /
  - CMakeLists.txt
  - lib/
    - assets/
    - pcs-detection/
    - raytracer/
    - CMakeLists.txt

The main **build** file is `lib/CMakeLists.txt`. Previously we
maintained several of those, however this led to duplication of
information. **Documentation** is maintained as a single main
[Doxyfile](http://www.doxygen.org/), plus source comments.

The `lib/` folder contains project source files, as well as some
assets for the UI. To build the project, create a `build/` folder,
`cd` into it, then run `cmake ../ && make`. Compiled binary will be
`lib/qtRaytracer`.

It is recommended to develop this project either in
[Arch Linux](https://www.archlinux.org/) or
[Ubuntu](http://www.ubuntu.com/) -- non-LTS, if possible. However,
if you choose Ubuntu, pay attention to the version of its packages, as
they quickly become out-of-date.

## Build Dependencies
- AntTweakBar
- Eigen 3.x+ - C++ linear algebra library
- Glew - OpenGL extension wrangler library
- Qt 5.x+ - GUI Toolkit
- cmake 2.6.x+ - Build management tool
- g++ 4.6+ - C/C++ compiler
- vcglib - Visualization and Computer Graphics library for dealing with triangle meshes
- Doxygen 1.8.x+ - Documentation Generator

It is recommended to use [Qt Creator](http://qt-project.org/) as your
main IDE together with your favorite text editor, and
[ccache](https://ccache.samba.org/) to speed up successive
compilations. [feh](http://feh.finalrewind.org/) is a simple image
viewer.

# To final users

# See also / Resources
- book companion page - http://www.raytracegroundup.com/
- cmake manual - http://cmake.org/cmake/help/v2.8.8/cmake.html
- Repositories
  - https://github.com/mikestaub/Ray-Tracer/
  - https://github.com/danoli3/Multithreaded-Ray-Tracer
  - https://code.google.com/p/pwsraytracer/
  - https://code.google.com/p/vcraytracer/
  - https://code.google.com/p/openglfun/
  - https://github.com/stefanoborini/python-raytracer
  - https://code.google.com/p/grounduptracer/
