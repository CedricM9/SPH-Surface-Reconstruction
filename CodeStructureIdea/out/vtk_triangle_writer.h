#pragma once

#include "triangle_writer.h"

class vtkTriangleWriter : public triangleWriter {
  public:
    vtkTriangleWriter();

    void write(const std::string& filename, const particleList& list);
};

#include "vtk_triangle_writer.cpp"
