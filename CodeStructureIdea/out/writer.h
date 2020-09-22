#ifndef WRITER_H
#define WRITER_H

#include <string>

#include "particle_list.h"

class writer {
  public:
    writer() {}

    virtual void write(const std::string& filename, const particleList& list) = 0;
};

#endif // WRITER_H
