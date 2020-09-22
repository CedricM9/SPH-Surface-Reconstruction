#pragma once

#include "reader.h"

class particleReader : public reader {
  public:
    particleReader() {}

    virtual particleList read(std::string filename) = 0;
};
