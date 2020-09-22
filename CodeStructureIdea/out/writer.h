#pragma once

#include <string>

#include "particle_list.h"

class writer {
  public:
    writer() {}

    virtual void write(const std::string& filename, const particleList& list) = 0;
};
