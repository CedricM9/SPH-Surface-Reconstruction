#pragma once

#include "writer.h"

class triangleWriter : public writer {
  public:
    triangleWriter() {}

    virtual void write(const std::string& filename, const particleList& list) = 0;
};
