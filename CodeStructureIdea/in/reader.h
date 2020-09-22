#ifndef READER_H
#define READER_H

#include <string>

#include "particle_list.h"

class reader {
  public:
    reader() {}

    virtual particleList read(std::string filename) = 0;
};

#endif // READER_H
