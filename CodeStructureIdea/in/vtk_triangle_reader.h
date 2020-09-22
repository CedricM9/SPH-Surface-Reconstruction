#ifndef VTK_TRIANGLE_READER_H
#define VTK_TRIANGLE_READER_H

#include "triangle_reader.h"

class vtkTriangleReader : public triangleReader {
  public:
    vtkTriangleReader();

    particleList read(std::string filename);
};

#include "vtk_triangle_reader.cpp"

#endif // VTK_TRIANGLE_READER_H
