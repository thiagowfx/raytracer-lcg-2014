Use this script to find include circular dependencies on a C/C++ project.

## References (HOWTO)
- https://stackoverflow.com/questions/9885656/how-can-i-find-circular-dependencies
- http://www.flourish.org/cinclude2dot/
- You can use either `neato` or `dot`.

## Command Line (from the root src folder...)
./cinclude2dot | neato -Tsvg > a.svg
./cinclude2dot --src src/ --include src/World,src/Utilities,src/Materials,src/Lights/,src/Cameras,src/GeometricObjects,src/BRDFs,src/Tracers | neato -Tsvg > a.svg
