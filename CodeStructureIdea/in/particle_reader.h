#ifndef PARTICLE_READER_H
#define PARTICLE_READER_H

#include "reader.h"

class particleReader : public reader {
  public:
    particleReader() {}

    virtual particleList read(std::string filename) = 0;
};

#endif // PARTICLE_READER_H
