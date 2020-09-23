#ifndef WRITER_H
#define WRITER_H

#include <string>

#include "particle_list.h"

class writer {
  public:
    writer() {}

    // should be particle list.
    virtual void write(const std::string& filename, const triangleList& list) = 0;
};

#endif // WRITER_H
