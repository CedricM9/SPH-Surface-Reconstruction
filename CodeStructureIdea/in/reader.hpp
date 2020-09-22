#pragma once

#include <string>

#include "particle_list.hpp"

template <typename T>
class reader {
  public:
    reader() {}

    virtual particleList<T> read(std::string filename) = 0;
};
