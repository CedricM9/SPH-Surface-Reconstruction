#ifndef PLY_TRIANGLE_WRITER_H
#define PLY_TRIANGLE_WRITER_H

#include "triangle_writer.h"

class plyTriangleWriter : public triangleWriter {
  public:
    plyTriangleWriter();

    void write(const std::string& filename, const particleList& list);
};

#include "ply_triangle_writer.cpp"

#endif // PLY_TRIANGLE_WRITER_H
