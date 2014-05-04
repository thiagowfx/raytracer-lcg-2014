#!/bin/sh
# Download and compiles all libraries necessary to the project.
EIGEN3="/usr/include/eigen3"

# AntTweakBar
[[ ! -d AntTweakBar ]] && git clone git://git.code.sf.net/p/anttweakbar/code AntTweakBar
cd AntTweakBar/src/
make
cd ../../

# glew
[[ ! -d glew ]] && git clone https://github.com/nigels-com/glew.git glew
cd glew/
make extensions
cd ../

# vcglib
[[ ! -d vcglib ]] && svn checkout svn://svn.code.sf.net/p/vcg/code/trunk/vcglib vcglib
rm -r vcglib/eigenlib/{Eigen,unsupported}
ln -s "${EIGEN3}"/Eigen       vcglib/eigenlib/
ln -s "${EIGEN3}"/unsupported vcglib/eigenlib/

# pcs-detection
[[ ! -d pcs-detection ]] && git clone git://git.lcg.ufrj.br/daniel-coutinho/pcs-detection.git pcs-detection
cd pcs-detection/
qmake && make
cd ../
