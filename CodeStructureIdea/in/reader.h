#pragma once

#include <string>

#include "particle_list.h"

class reader {
  public:
    reader() {}

    virtual particleList read(std::string filename) = 0;
};
