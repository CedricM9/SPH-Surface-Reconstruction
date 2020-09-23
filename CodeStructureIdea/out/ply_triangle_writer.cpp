#include "happly.h" 

plyTriangleWriter::plyTriangleWriter() {}

void plyTriangleWriter::write(const std::string& filename, const triangleList& list) {
    // TODO: implement function writing file from triangle list.

    // Create mesh data
    std::vector<std::array<double, 3>> meshVertexPositions = list.getParticleVector();
    std::vector<std::vector<size_t>> meshFaceIndices = list.getFaceVector();
    
    // Create an empty object
    happly::PLYData plyOut;

    // Add mesh data (elements are created automatically).
    plyOut.addVertexPositions(meshVertexPositions);
    plyOut.addFaceIndices(meshFaceIndices);

    // Write the object to file.
    plyOut.write(filename, happly::DataFormat::ASCII);
}

