#pragma once

#include "reader.h"

class triangleReader : public reader {
  public:
    triangleReader() {}

    virtual particleList read(std::string filename) = 0;
};
