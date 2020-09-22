#pragma once

#include "triangle_writer.hpp"

template<typename T>
class plyTriangleWriter : public triangleWriter<T> {
  public:
    plyTriangleWriter();

    void write(const std::string& filename, const particleList<T>& list);
};

#include "ply_triangle_writer.cpp"
