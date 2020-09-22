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
    particle p1(1.0, 0.0, 0.0), p2(0.0, 1.0, 0.0);

    // Create particle list.
    particleList particles;
    particles.addParticle(p1);
    particles.addParticle(p2);
    particles.addParticle(0.0, 0.0, 1.0);

    // Index a particle.
    particle p = particles.getParticle(0);
    std::cout << "first particle of list: x = " << p.x() << ", y = " << p.y() << ", z = " << p.z() << std::endl;

    // Create triangle list.
    triangleList triangles(particles);
    triangles.addTriangle(0, 1, 2);

    // Index a triangle.
    std::array<particle, 3> t = triangles.getTriangle(0);
    std::cout << "third particle of first triangle: x = " << t[2].x() << ", y = " << t[2].y() << ", z = " << t[2].z() << std::endl;

    // Create readers.
    partioParticleReader partioParticleIn;
    particles = partioParticleIn.read("filename.bgeo");
    vtkParticleReader vtkParticleIn;
    particles = vtkParticleIn.read("filename.vtk");
    vtkTriangleReader vtkTriangleIn;
    particles = vtkTriangleIn.read("filename.vtk");

    // Create writers.
    vtkTriangleWriter vtkTriangleOut;
    vtkTriangleOut.write("filename.vtk", particles);
    plyTriangleWriter plyTriangleOut;
    plyTriangleOut.write("filename.ply", particles);

    // Find nearest neighbors.
    spatialHashingNeighborhoodSearch nSearch;
    std::shared_ptr<spatialHashingNeighborhoodSearch> nSearchPointer = std::make_shared<spatialHashingNeighborhoodSearch>(nSearch);
    std::vector<std::vector<int>> nearestNeighbors = nSearch.find({}, 0.5);

    // Evaluate cubic spline kernel.
    cubicSplineKernel kernel;
    std::shared_ptr<cubicSplineKernel> kernelPointer = std::make_shared<cubicSplineKernel>(kernel);
    double s = kernel.evaluate(2.0);

    // Evaluate dimensionless level set function.
    dimensionlessLevelSetFunction levelSet;
    std::shared_ptr<dimensionlessLevelSetFunction> levelSetPointer = std::make_shared<dimensionlessLevelSetFunction>(levelSet);
    double phi = levelSet.evaluate(particles);

    // Reconstruct a surface using marching cubes algorithm.
    marchingCubesReconstructor reconstructor;
    triangleList result = reconstructor.reconstruct(particles, levelSetPointer, nSearchPointer, kernelPointer);

    return 0;
}
