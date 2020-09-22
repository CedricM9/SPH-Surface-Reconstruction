#pragma once

#include "triangle_reader.hpp"

class vtkTriangleReader : public triangleReader {
  public:
    vtkTriangleReader();

    particleList read(std::string filename);
};

#include "vtk_triangle_reader.cpp"
