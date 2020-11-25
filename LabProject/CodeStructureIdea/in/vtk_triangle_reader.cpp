#include <array>
#include <string>
#include <vector>

#include "surfrec_io/extern/vtkio/VTKStream.h"

vtkTriangleReader::vtkTriangleReader() {}

particleList vtkTriangleReader::read(std::string filename) {
    // Create a VTK stream to read in the file.
    vtkio::VTKStream vtk_stream;
    vtk_stream.read(filename);
    vtk_stream.points.castInplace<float>();
    
    // Extract the particle information from the VTK stream.
    std::vector<std::array<float, 3>> particles(vtk_stream.getNumberOfPoints());
    vtk_stream.getPointsNestedIterator(particles.begin(), particles.end(), 3);
    std::vector<std::array<int, 3>> triangles(vtk_stream.getNumberOfCells());
    vtk_stream.getCellsNestedIterator(triangles.begin(), triangles.end()); //, vtkio::tables::CellType::Triangle);

    // Create a data structure particleList from the read in information.
    triangleList list;
    for (const auto& particle : particles) {
        // TODO: add overloaded function that takes a float array
        list.addParticle(particle[0], particle[1], particle[2]);
    }
    for (const auto& triangle : triangles) {
        // TODO: add overloaded function that takes an int array
        list.addTriangle(triangle[0], triangle[2], triangle[3]);
    }
    return list;
}
