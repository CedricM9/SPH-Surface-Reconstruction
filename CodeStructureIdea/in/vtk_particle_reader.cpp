#include <Eigen/Dense>
#include "VTKStream.h"

using Vector3f = Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;

vtkParticleReader::vtkParticleReader() {}

particleList vtkParticleReader::read(std::string filename) {
    particleList list;

    vtkio::VTKStream vtk_stream;
    vtk_stream.read(filename);
    vtk_stream.points.castInplace<float>();
    
    std::vector<Vector3f> particles(vtk_stream.getNumberOfPoints());
//    vtk_stream.getPointsNestedIterator(particles.begin(), particles.end(), 3);

    for (const auto& particle : particles) {
        list.addParticle(particle(0), particle(1), particle(2));
    }

    return list;
}

