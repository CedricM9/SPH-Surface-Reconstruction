#pragma once

#include <string>

#include "particle_list.hpp"

class writer {
  public:
    writer() {}

    virtual void write(const std::string& filename, const particleList& list) = 0;
};
