#ifndef _MYBOOST_MINE_
#define _MYBOOST_MINE_

#include <fstream>
#include <iostream>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
using boost::serialization::make_nvp;

template<class T>
void save_xml(const T &t, const char* filename) {
  std::ofstream ofs(filename);
  boost::archive::xml_oarchive oa(ofs);
  oa << BOOST_SERIALIZATION_NVP(t);
}

template<class T>
void load_xml(T &t, const char* filename) {
  std::ifstream ifs(filename);
  boost::archive::xml_iarchive ia(ifs);
  ia >> BOOST_SERIALIZATION_NVP(t);
}

#endif // _MYBOOST_MINE_
