#include <array>
#include <iostream>

#include "particle_list.h"
#include "triangle_list.h"

#include "partio_particle_reader.h"
#include "vtk_particle_reader.h"
#include "vtk_triangle_reader.h"

#include "ply_triangle_writer.h"
#include "vtk_triangle_writer.h"

#include "spatial_hashing_neighborhood_search.h"
#include "cubic_spline_kernel.h"
#include "dimensionless_level_set_function.h"

#include "marching_cubes_reconstructor.h"

#include "open_mesh_processor.h"

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
    particles = partioParticleIn.read("/media/sf_Software_Lab/SPH-Surface-Reconstruction/SimulationOutputTestData/bgeo/ParticleData_Fluid_163.bgeo");
    vtkParticleReader vtkParticleIn;
    //particles = vtkParticleIn.read("/media/sf_Software_Lab/SPH-Surface-Reconstruction/SimulationOutputTestData/vtk/ParticleData_Fluid_163.vtk");
    vtkTriangleReader vtkTriangleIn;
    particles = vtkTriangleIn.read("filename.vtk");

    // Create writers.
    vtkTriangleWriter vtkTriangleOut;
    vtkTriangleOut.write("filename.vtk", triangles);
    plyTriangleWriter plyTriangleOut;
    plyTriangleOut.write("filename.ply", triangles);

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
    //triangleList result = reconstructor.reconstruct(particles, levelSetPointer, nSearchPointer, kernelPointer);
    particleList vertices;
    for (int i = 0; i < 8; ++i) vertices.addParticle(p1);
    triangleList result = triangles;  // reconstructor.reconstruct(vertices, {}, particles, levelSetPointer, nSearchPointer, kernelPointer);

    // Postprocessing.
    openMeshProcessor postprocessor;
    result = postprocessor.smooth(result);
    result = postprocessor.simplify(result);

    return 0;
}
