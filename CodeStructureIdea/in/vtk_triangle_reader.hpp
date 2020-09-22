#pragma once

#include "triangle_reader.hpp"

template<typename T>
class vtkTriangleReader : public triangleReader<T> {
  public:
    vtkTriangleReader();

    particleList<T> read(std::string filename);
};

#include "vtk_triangle_reader.cpp"
