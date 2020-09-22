#pragma once

#include "reader.hpp"

template<typename T>
class particleReader : public reader<T> {
  public:
    particleReader() {}

    virtual particleList<T> read(std::string filename) = 0;
};
