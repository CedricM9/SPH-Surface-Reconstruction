#include <array>
#include <cassert>
#include <vector>

#include "happly.h" 

plyTriangleWriter::plyTriangleWriter() {}

void plyTriangleWriter::write(const std::string& filename, const particleList& list) {
    // Convert particleList to derived class triangleList.
    triangleList const* tlist = dynamic_cast<triangleList const*>(&list);
    assert(tlist);

    // Create mesh data.
    std::vector<std::array<float, 3>> meshVertexPositionsFloat = tlist->getParticleVector();
    std::vector<std::array<double, 3>> meshVertexPositions(meshVertexPositionsFloat.size(), {0.0, 0.0, 0.0});
    for (int i = 0; i < meshVertexPositionsFloat.size(); ++i) {
        meshVertexPositions[i][0] = meshVertexPositionsFloat[i][0];
        meshVertexPositions[i][1] = meshVertexPositionsFloat[i][1];
        meshVertexPositions[i][2] = meshVertexPositionsFloat[i][2];
    }
    std::vector<std::vector<size_t>> meshFaceIndices = tlist->getFaceVector();
    
    // Create an empty object.
    happly::PLYData plyOut;

    // Add mesh data (elements are created automatically).
    plyOut.addVertexPositions(meshVertexPositions);
    plyOut.addFaceIndices(meshFaceIndices);

    // Write the objects to the file.
    plyOut.write(filename, happly::DataFormat::ASCII);
}

