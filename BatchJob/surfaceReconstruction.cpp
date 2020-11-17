#include <cassert>
#include <experimental/filesystem>
#include <string>

#include "particle_list.h"
#include "triangle_list.h"

#include "partio_particle_reader.h"
#include "vtk_particle_reader.h"

#include "ply_triangle_writer.h"
#include "vtk_triangle_writer.h"

#include "spatial_hashing_neighborhood_search.h"
#include "cubic_spline_kernel.h"
#include "spiky_kernel.h"
#include "dimensionless_level_set_function.h"

#include "marching_cubes_reconstructor.h"

#include "open_mesh_processor.h"

int main(int argc, char* argv[]) {
    // Read in command line arguments.
    assert(argc == 12);
    std::string inputFileFormat         = argv[1];  // "bgeo" or "vtk"
    std::string outputFileFormat        = argv[2];  // "ply" or "vtk"

    std::string neighborhoodSearch      = argv[3];  // only "spatialHashing"
    std::string kernelFunction          = argv[4];  // "cubicSpline" or "spiky"
    std::string levelSetFunction        = argv[5];  // only "dimensionless"
    std::string reconstructionMethod    = argv[6];  // only "marchingCubes"

    std::string inputFolder             = argv[7];  // absolute path to simulation frames
    std::string outputFolder            = argv[8];  // absolute path to where the output is to be stored

    float smoothingLength               = std::stof(argv[9]);
    float compactSupport                = std::stof(argv[10]);
    int openMPThreads                   = std::stoi(argv[11]);

    // Create correct reader.
    std::shared_ptr<particleReader> particleIn;
    if (inputFileFormat == "bgeo") {
        partioParticleReader partioParticleIn;
        particleIn.reset(&partioParticleIn);
    } else if (inputFileFormat == "vtk") {
        vtkParticleReader vtkParticleIn;
        particleIn.reset(&vtkParticleIn);
    } else {
        std::cerr << "Input file format not supported. Has to be bgeo or vtk." << std::endl;
    }

    // Create correct writer.
    std::shared_ptr<triangleWriter> triangleOut;
    if (outputFileFormat == "bgeo") {
        plyTriangleWriter plyTriangleOut;
        triangleOut.reset(&plyTriangleOut);
    } else if (outputFileFormat == "vtk") {
        vtkTriangleWriter vtkTriangleOut;
        triangleOut.reset(&vtkTriangleOut);
    } else {
        std::cerr << "Output file format not supported. Has to be ply or vtk." << std::endl;
    }

    // Create pointer to the correct neighborhood search object.
    std::shared_ptr<spatialHashingNeighborhoodSearch> nSearchPointer;
    if (neighborhoodSearch == "spatialHasing") {
        spatialHashingNeighborhoodSearch nSearch;
        nSearchPointer = std::make_shared<spatialHashingNeighborhoodSearch>(nSearch);
    } else {
        std::cerr << "Neighborhood search not supported. Has to be spatialHashing." << std::endl;
    }

    // Create pointer to the correct SPH interpolation kernel.
    std::shared_ptr<cubicSplineKernel> kernelPointer;
    if (kernelFunction == "cubicSpline") {
        cubicSplineKernel kernel;
        kernelPointer = std::make_shared<cubicSplineKernel>(kernel);
    } else if (kernelFunction == "spiky") {
//        spikyKernel kernel;
//        kernelPointer = std::make_shared<cubicSplineKernel>(kernel);
    } else {
        std::cerr << "Kernel function type not supported. Has to be cubicSpline or spiky." << std::endl;
    }

    // Create pointer to the correct level set function.
    std::shared_ptr<dimensionlessLevelSetFunction> levelSetPointer;
    if (levelSetFunction == "dimensionless") {
        dimensionlessLevelSetFunction levelSet;
        levelSetPointer = std::make_shared<dimensionlessLevelSetFunction>(levelSet);
    } else {
        std::cerr << "Level set function type not supported. Has to be dimensionless." << std::endl;
    }

    // Create pointer to the correct reconstructor.
    std::shared_ptr<surfaceReconstructor> reconstructionPointer;
    if (reconstructionMethod == "marchingCubes") {
        marchingCubesReconstructor reconstructor;
        //reconstructionPointer = std::make_shared<surfaceReconstructor>(reconstructor);
        reconstructionPointer.reset(&reconstructor);
    } else {
        std::cerr << "Surface reconstruction method not supported. Has to be marchingCubes." << std::endl;
    }

    // TODO: add openmp    
    for (const auto & entry : std::experimental::filesystem::directory_iterator(inputFolder)) {
        std::cout << entry.path() << std::endl;
        std::string inputFile = entry.path();
        std::string outputFile = entry.path();

        // Reconstruct a surface using marching cubes algorithm.
        particleList particles = particleIn->read(inputFolder);
        graph reconstructionGraph(particles, 1);
        triangleList result = reconstructionPointer->reconstruct(
            reconstructionGraph, particles, smoothingLength, compactSupport, levelSetPointer, nSearchPointer, kernelPointer);
        triangleOut->write(outputFile, result);
    }

    // Postprocessing.
    //openMeshProcessor postprocessor;
    //result = postprocessor.smooth(result);
    //result = postprocessor.simplify(result);
    //vtkTriangleOut.write("test_result5.vtk", result);
    //result = postprocessor.simplify(result);

    return 0;
}
