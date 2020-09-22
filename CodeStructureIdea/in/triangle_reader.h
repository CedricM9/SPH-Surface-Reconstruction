#ifndef TRIANGLE_READER_H
#define TRIANGLE_READER_H

#include "reader.h"

class triangleReader : public reader {
  public:
    triangleReader() {}

    virtual particleList read(std::string filename) = 0;
};

#endif // TRIANGLE_READER_H
