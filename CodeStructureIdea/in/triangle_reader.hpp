#pragma once

#include "reader.hpp"

class triangleReader : public reader {
  public:
    triangleReader() {}

    virtual particleList read(std::string filename) = 0;
};
