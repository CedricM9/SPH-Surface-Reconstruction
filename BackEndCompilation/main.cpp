#include <array>
#include <iostream>

#include "particle_list.h"
#include "triangle_list.h"

#include "partio_particle_reader.h"
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

    // Neighborhood search for one particle.
    spatialHashingNeighborhoodSearch nsearch;
    std::vector<std::vector<unsigned int>> all_neighbors = nsearch.find(particles, 0.9);
    std::vector<unsigned int> neighbors = nsearch.find(particles, 0.9, 0.5, 0.5, 0.5);
    std::cout << "neighbors of particle 0.5 0.5 0.5:" << std::endl;
    for (auto neighbor : neighbors) {
        std::cout << neighbor << "  ";
    }
    std::cout << std::endl;

    // Create bgeo reader and read in test data.
    partioParticleReader partioParticleIn;
    particles = partioParticleIn.read("../LabProject/TestData/Test_Surface.bgeo");

    // Create vtk writer.
    vtkTriangleWriter vtkTriangleOut;

    // Create pointer for neighborhood search.
    std::shared_ptr<spatialHashingNeighborhoodSearch> nSearchPointer = std::make_shared<spatialHashingNeighborhoodSearch>(nsearch);

    // Create pointer to cubic spline kernel.
    cubicSplineKernel kernel;
    std::shared_ptr<cubicSplineKernel> kernelPointer = std::make_shared<cubicSplineKernel>(kernel);

    // Create pointer to dimensionless level set function.
    dimensionlessLevelSetFunction levelSet;
    std::shared_ptr<dimensionlessLevelSetFunction> levelSetPointer = std::make_shared<dimensionlessLevelSetFunction>(levelSet);

    // Reconstruct a surface using marching cubes algorithm and write result to vtk file.
    marchingCubesReconstructor reconstructor;
    graph g(particles, 20);
    float h = 0.028;    // smoothing length
    float r = 2*h;      // compact support radius
    float c = 0.8;      // iso-value
    triangleList result = reconstructor.reconstruct(g, particles, h, r, c, levelSetPointer, nSearchPointer, kernelPointer);
    std::cout << "result: #particles = " << result.getNumberOfParticles() << ", #triangles = " << result.getNumberOfTriangles() << std::endl;
    vtkTriangleOut.write("test_result.vtk", result);

    // Postprocessing.
    openMeshProcessor postprocessor;
    
    // Smooth the mesh 50 times and write output to vtk file.
    triangleList smoothedResult = postprocessor.smooth(result, 50);
    vtkTriangleOut.write("test_result_smoothed.vtk", smoothedResult);
    std::cout << "result after smoothing: #particles = " << smoothedResult.getNumberOfParticles() << ", #triangles = " << smoothedResult.getNumberOfTriangles() << std::endl;

    // Decimate mesh and write output to vtk file.
    triangleList simplifiedResult = postprocessor.simplify(result);
    std::cout << "result after simplification: #particles = " << simplifiedResult.getNumberOfParticles() << ", #triangles = " << simplifiedResult.getNumberOfTriangles() << std::endl;
    vtkTriangleOut.write("test_result_simplified.vtk", simplifiedResult);

    return 0;
}
