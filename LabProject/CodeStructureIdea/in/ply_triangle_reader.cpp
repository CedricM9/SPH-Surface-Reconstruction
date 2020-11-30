#include <array>
#include <cassert>
#include <vector>

#include "happly.h" 

plyTriangleReader::plyTriangleReader() {}

triangleList plyTriangleReader::read(const std::string &filename) {
    // Open the file.
    happly::PLYData plyIn(filename);
    plyIn.validate();

    // Get mesh data.
    std::vector<std::array<double, 3>> meshVertexPositions = plyIn.getVertexPositions();
    std::vector<std::vector<size_t>> meshFaceIndices = plyIn.getFaceIndices();

    // Create a data structure triangleList from the read in information.
    triangleList list;
    for (const auto& particle : meshVertexPositions) {
        list.addParticle(particle[0], particle[1], particle[2]);
    }
    for (const auto& triangle : meshFaceIndices) {
        list.addTriangle(triangle[0], triangle[1], triangle[2]);
    }
    return list;
}

