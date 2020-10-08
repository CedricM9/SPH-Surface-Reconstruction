#include <cassert>
#include "happly.h" 

plyTriangleWriter::plyTriangleWriter() {}

void plyTriangleWriter::write(const std::string& filename, const particleList& list) {
    // Convert particleList to derived class triangleList.
    triangleList const* tlist = dynamic_cast<triangleList const*>(&list);
    assert(tlist);

    // Create mesh data.
    std::vector<std::array<double, 3>> meshVertexPositions = tlist->getParticleVector();
    std::vector<std::vector<size_t>> meshFaceIndices = tlist->getFaceVector();
    
    // Create an empty object.
    happly::PLYData plyOut;

    // Add mesh data (elements are created automatically).
    plyOut.addVertexPositions(meshVertexPositions);
    plyOut.addFaceIndices(meshFaceIndices);

    // Write the objects to the file.
    plyOut.write(filename, happly::DataFormat::ASCII);
}

