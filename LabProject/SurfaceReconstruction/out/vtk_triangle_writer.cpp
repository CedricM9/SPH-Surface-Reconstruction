#include <array>
#include <cassert>
#include <vector>

#include "VTKStream.h"

vtkTriangleWriter::vtkTriangleWriter() {}

void vtkTriangleWriter::write(const std::string& filename, const particleList& list) {
    // Convert particleList to derived class triangleList.
    triangleList const* tlist = dynamic_cast<triangleList const*>(&list);
    assert(tlist);

    // Create mesh data.
    std::vector<std::array<float, 3>> meshVertexPositions = tlist->getParticleVector();
    std::vector<std::vector<size_t>> meshFaceIndices = tlist->getFaceVector();
    
    // Create a VTK stream handling the actual conversion to VTK file format.
    vtkio::VTKStream vtk_stream;

    // Add the particle positions and triangles indices to the VTK stream.
    vtk_stream.setPointsNestedIterator(meshVertexPositions.begin(), meshVertexPositions.end());
    vtk_stream.setCellsNestedIterator(meshFaceIndices.begin(), meshFaceIndices.end(), vtkio::tables::CellType::Triangle);

    // Write the objects to the file.
    vtk_stream.write(filename, true); //false);
}

