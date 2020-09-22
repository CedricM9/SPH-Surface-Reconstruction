#pragma once

#include "triangle_writer.hpp"

template<typename T>
class vtkTriangleWriter : public triangleWriter<T> {
  public:
    vtkTriangleWriter();

    void write(const std::string& filename, const particleList<T>& list);
};

#include "vtk_triangle_writer.cpp"
