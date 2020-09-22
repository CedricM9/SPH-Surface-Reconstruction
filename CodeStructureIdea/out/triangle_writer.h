#ifndef TRIANGLE_WRITER_H
#define TRIANGLE_WRITER_H

#include "writer.h"

class triangleWriter : public writer {
  public:
    triangleWriter() {}

    virtual void write(const std::string& filename, const particleList& list) = 0;
};

#endif // TRIANGLE_WRITER_H
