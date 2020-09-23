#ifndef VTK_TRIANGLE_WRITER_H
#define VTK_TRIANGLE_WRITER_H

#include "triangle_writer.h"

class vtkTriangleWriter : public triangleWriter {
  public:
    vtkTriangleWriter();

    void write(const std::string& filename, const triangleList& list);
};

#include "vtk_triangle_writer.cpp"

#endif // VTK_TRIANGLE_WRITER_H
