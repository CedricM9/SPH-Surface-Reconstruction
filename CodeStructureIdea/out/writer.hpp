#pragma once

#include <string>

#include "particle_list.hpp"

template <typename T>
class writer {
  public:
    writer() {}

    virtual void write(const std::string& filename, const particleList<T>& list) = 0;
};
