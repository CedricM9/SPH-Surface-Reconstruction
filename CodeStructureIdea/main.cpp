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

    // Neighborhood search for one particle.
    spatialHashingNeighborhoodSearch nsearch;
    std::vector<std::vector<unsigned int>> all_neighbors = nsearch.find(particles, 0.9);
    std::vector<unsigned int> neighbors = nsearch.find(particles, 0.9, 0.5, 0.5, 0.5);
    std::cout << "neighbors of particle 0.5 0.5 0.5:" << std::endl;
    for (auto neighbor : neighbors) {
        std::cout << neighbor << "  ";
    }
    std::cout << std::endl;

    // Create readers.
    partioParticleReader partioParticleIn;
    //  particles = partioParticleIn.read("/media/sf_Software_Lab/SPH-Surface-Reconstruction/SimulationOutputTestData/bgeo/ParticleData_Fluid_163.bgeo");
    vtkParticleReader vtkParticleIn;
    //particles = vtkParticleIn.read("/media/sf_Software_Lab/SPH-Surface-Reconstruction/SimulationOutputTestData/vtk/ParticleData_Fluid_163.vtk");
    vtkTriangleReader vtkTriangleIn;
    particles = vtkTriangleIn.read("ParticleData_Fluid_1.vtk");

    // Create writers.
    vtkTriangleWriter vtkTriangleOut;
    vtkTriangleOut.write("filename.vtk", triangles);
    //  plyTriangleWriter plyTriangleOut;
    //  plyTriangleOut.write("filename.ply", triangles);

    // Find nearest neighbors.
    spatialHashingNeighborhoodSearch nSearch;
    std::shared_ptr<spatialHashingNeighborhoodSearch> nSearchPointer = std::make_shared<spatialHashingNeighborhoodSearch>(nSearch);
    std::vector<std::vector<unsigned int>> nearestNeighbors = nSearch.find({}, 0.5);

    // Evaluate cubic spline kernel.
    cubicSplineKernel kernel;
    std::shared_ptr<cubicSplineKernel> kernelPointer = std::make_shared<cubicSplineKernel>(kernel);
    //double s = kernel.evaluate(2.0);

    // Evaluate dimensionless level set function.
    dimensionlessLevelSetFunction levelSet;
    std::shared_ptr<dimensionlessLevelSetFunction> levelSetPointer = std::make_shared<dimensionlessLevelSetFunction>(levelSet);
    //double phi = levelSet.evaluate(particles);

    // Reconstruct a surface using marching cubes algorithm.
    marchingCubesReconstructor reconstructor;
    //triangleList result = reconstructor.reconstruct(particles, levelSetPointer, nSearchPointer, kernelPointer);
    /*
    particleList vertices;
    for (int i = 0; i < 8; ++i) {
        particle p(i/10.0, i/10.0, i/10.0);
        //vertices.addParticle(p);
    }
    */
    //vertices.addParticle(0.5,0,0);
    //vertices.addParticle(0,0,0);
    //vertices.addParticle(0.5,0.5,0);
    //vertices.addParticle(0.5,0,0.5);
    //vertices.addParticle(0,0.5,0.5);
    //vertices.addParticle(0.5,0.5,0.5);
    //vertices.addParticle(0,0,0.5);
    //vertices.addParticle(0,0.5,0);
    //particleList particles;
/*    
    int n = 3;
    float scaling = 20.0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k=0; k<3; ++k) {
                particle p(k/scaling, j/scaling, i/scaling);
                particles.addParticle(p);
            }
        }
    }
 */  
    //particles = partioParticleIn.read("/media/sf_Software_Lab/SPH-Surface-Reconstruction/SimulationOutputTestData/bgeo/ParticleData_Fluid_13.bgeo");
    graph g(particles, 20);
    float h = 0.028;  // smoothing length
    float r = 2*h;
    float c = 0.8;
    triangleList result = reconstructor.reconstruct(g, particles, h, r, c, levelSetPointer, nSearchPointer, kernelPointer);
    //  plyTriangleOut.write("test_result2.ply", result);
    vtkTriangleOut.write("test_result.vtk", result);

    // Postprocessing.
    openMeshProcessor postprocessor;
    triangleList result2 = postprocessor.smooth(result, 50);
    vtkTriangleOut.write("test_result_smoothed.vtk", result2);
    std::cout << "result: particles = " << result.getNumberOfParticles() << ", triangles = " << result.getNumberOfTriangles() << std::endl;
    triangleList result3 = postprocessor.simplify(result);
    std::cout << "result after simplification: particles = " << result3.getNumberOfParticles() << ", triangles = " << result3.getNumberOfTriangles() << std::endl;
    vtkTriangleOut.write("test_result_simplified.vtk", result3);

    triangleList mesh;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                particle q(i, j, k);
                mesh.addParticle(q);
            }
        }
    }
    mesh.addTriangle(1, 2, 0);
    mesh.addTriangle(3, 2, 1);
    mesh.addTriangle(0, 5, 1);
    mesh.addTriangle(0, 4, 5);
    mesh.addTriangle(5, 7, 1);
    mesh.addTriangle(1, 7, 3);
    mesh.addTriangle(3, 6, 2);
    mesh.addTriangle(7, 6, 3);
    mesh.addTriangle(7, 5, 4);
    mesh.addTriangle(7, 4, 6);
    mesh.addTriangle(0, 2, 6);
    mesh.addTriangle(0, 6, 4);
    
    vtkTriangleOut.write("triangle_mesh.vtk", mesh);
    triangleList smoothed = postprocessor.smooth(mesh, 1);
    vtkTriangleOut.write("smoothed_triangle_mesh.vtk", smoothed);

    return 0;
}
