#pragma once

#include "writer.hpp"

template<typename T>
class triangleWriter : public writer<T> {
  public:
    triangleWriter() {}

    virtual void write(const std::string& filename, const particleList<T>& list) = 0;
};
