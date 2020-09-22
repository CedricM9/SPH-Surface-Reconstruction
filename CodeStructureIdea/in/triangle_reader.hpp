#pragma once

#include "reader.hpp"

template<typename T>
class triangleReader : public reader<T> {
  public:
    triangleReader() {}

    virtual particleList<T> read(std::string filename) = 0;
};
