#pragma once

#include "reader.hpp"

class particleReader : public reader {
  public:
    particleReader() {}

    virtual particleList read(std::string filename) = 0;
};
