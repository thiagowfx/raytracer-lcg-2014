#include "PrimitivaDaniel.h"

// FIXME construtor
PrimitivaDaniel::PrimitivaDaniel() {}


// FIXME outro construtor
PrimitivaDaniel::PrimitivaDaniel (const PrimitivaDaniel& pd) {}


// FIXME operator=
PrimitivaDaniel& PrimitivaDaniel::operator= (const PrimitivaDaniel& rhs) {
  if (this != &rhs) {
  }

  return *this;
}


PrimitivaDaniel* PrimitivaDaniel::clone() const {
  return new PrimitivaDaniel(*this);
}


// FIXME destrutor
PrimitivaDaniel::~PrimitivaDaniel() {}


// FIXME operação principal
bool PrimitivaDaniel::hit(const Ray& ray, double& t, ShadeRec& s) const {

  // TODO: interface para a função hit original
  // TODO: obter normal (...)
  // TODO: vcg <-> Eigen
  return false;
}
