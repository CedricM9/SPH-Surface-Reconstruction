#pragma once

#include "triangle_writer.hpp"

class plyTriangleWriter : public triangleWriter {
  public:
    plyTriangleWriter();

    void write(const std::string& filename, const particleList& list);
};

#include "ply_triangle_writer.cpp"
