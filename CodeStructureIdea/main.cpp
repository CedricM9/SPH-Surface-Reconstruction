#include <array>
#include <iostream>

#include "particle_list.hpp"
#include "triangle_list.hpp"

#include "partio_particle_reader.hpp"
#include "vtk_particle_reader.hpp"
#include "vtk_triangle_reader.hpp"

#include "ply_triangle_writer.hpp"
#include "vtk_triangle_writer.hpp"

#include "spatial_hashing_neighborhood_search.hpp"
#include "cubic_spline_kernel.hpp"
#include "dimensionless_level_set_function.hpp"

#include "marching_cubes_reconstructor.hpp"

int main() {
    // Create particles.
    particle<double> p1(1.0, 0.0, 0.0), p2(0.0, 1.0, 0.0);

    // Create particle list.
    particleList<double> particles;
    particles.addParticle(p1);
    particles.addParticle(p2);
    particles.addParticle(0.0, 0.0, 1.0);

    // Index a particle.
    particle<double> p = particles.getParticle(0);
    std::cout << "first particle of list: x = " << p.x() << ", y = " << p.y() << ", z = " << p.z() << std::endl;

    // Create triangle list.
    triangleList<double> triangles(particles);
    triangles.addTriangle(0, 1, 2);

    // Index a triangle.
    std::array<particle<double>, 3> t = triangles.getTriangle(0);
    std::cout << "third particle of first triangle: x = " << t[2].x() << ", y = " << t[2].y() << ", z = " << t[2].z() << std::endl;

    // Create readers.
    partioParticleReader<double> partioParticleIn;
    particles = partioParticleIn.read("filename.bgeo");
    vtkParticleReader<double> vtkParticleIn;
    particles = vtkParticleIn.read("filename.vtk");
    vtkTriangleReader<double> vtkTriangleIn;
    particles = vtkTriangleIn.read("filename.vtk");

    // Create writers.
    vtkTriangleWriter<double> vtkTriangleOut;
    vtkTriangleOut.write("filename.vtk", particles);
    plyTriangleWriter<double> plyTriangleOut;
    plyTriangleOut.write("filename.ply", particles);

    // Find nearest neighbors.
    spatialHashingNeighborhoodSearch<double> nSearch;
    std::shared_ptr<spatialHashingNeighborhoodSearch<double>> nSearchPointer = std::make_shared<spatialHashingNeighborhoodSearch<double>>(nSearch);
    std::vector<std::vector<int>> nearestNeighbors = nSearch.find({}, 0.5);

    // Evaluate cubic spline kernel.
    cubicSplineKernel<double> kernel;
    std::shared_ptr<cubicSplineKernel<double>> kernelPointer = std::make_shared<cubicSplineKernel<double>>(kernel);
    double s = kernel.evaluate(2.0);

    // Evaluate dimensionless level set function.
    dimensionlessLevelSetFunction<double> levelSet;
    std::shared_ptr<dimensionlessLevelSetFunction<double>> levelSetPointer = std::make_shared<dimensionlessLevelSetFunction<double>>(levelSet);
    double phi = levelSet.evaluate(particles);

    // Reconstruct a surface using marching cubes algorithm.
    marchingCubesReconstructor<double> reconstructor;
    triangleList<double> result = reconstructor.reconstruct(particles, levelSetPointer, nSearchPointer, kernelPointer);

    return 0;
}
