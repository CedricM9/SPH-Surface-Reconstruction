#include <array>
#include <string>
#include <vector>

#include "surfrec_io/extern/vtkio/VTKStream.h"

vtkParticleReader::vtkParticleReader() {}

particleList vtkParticleReader::read(std::string filename) {
    // Create a VTK stream to read in the file.
    vtkio::VTKStream vtk_stream;
    vtk_stream.read(filename);
    vtk_stream.points.castInplace<float>();
    
    // Extract the particle information from the VTK stream.
    std::vector<std::array<float, 3>> particles(vtk_stream.getNumberOfPoints());
    vtk_stream.getPointsNestedIterator(particles.begin(), particles.end(), 3);

    // Create a data structure particleList from the read in information.
    particleList list;
    for (const auto& particle : particles) {
        // TODO: add overloaded function that takes a float array
        list.addParticle(particle[0], particle[1], particle[2]);
    }
    return list;
}

