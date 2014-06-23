#!/bin/sh
# Download and compile all libraries necessary to the project.
EIGEN3="/usr/include/eigen3"
WORKING_DIR=$(pwd)

msg() {
    echo "--> $*"
}

# AntTweakBar
if [[ ! -d AntTweakBar ]];
then
    git clone git://git.code.sf.net/p/anttweakbar/code AntTweakBar
fi
cd AntTweakBar/
git pull origin master
cd src/
make
msg "AntTweakBar OK"
cd $WORKING_DIR

# glew
if [[ ! -d glew ]]; then
    git clone https://github.com/nigels-com/glew.git glew
fi
cd glew/
git pull origin master
make extensions && make
msg "glew OK"
cd $WORKING_DIR

# vcglib
if [[ ! -d vcglib ]]; then
    svn checkout svn://svn.code.sf.net/p/vcg/code/trunk/vcglib vcglib
fi
cd vcglib/
# svn update
rm -r eigenlib/{Eigen,unsupported}
ln -s "${EIGEN3}"/Eigen       eigenlib/
ln -s "${EIGEN3}"/unsupported eigenlib/
msg "vcglib OK"
cd $WORKING_DIR

# pcs-detection
if [[ ! -d pcs-detection ]]; then
    git clone git://git.lcg.ufrj.br/daniel-coutinho/pcs-detection.git pcs-detection
fi
cd pcs-detection/
git pull origin master
qmake && make
msg "pcs-detection OK"
cd $WORKING_DIR
