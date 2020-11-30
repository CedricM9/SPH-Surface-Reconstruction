#include <cassert>
#include <experimental/filesystem>
#include <string>
#include <vector>

#include <omp.h>

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
    assert(argc == 13);
    std::string inputFileFormat         = argv[1];  // "bgeo" or "vtk"
    std::string outputFileFormat        = argv[2];  // "ply" or "vtk"

    std::string neighborhoodSearch      = argv[3];  // only "spatialHashing"
    std::string kernelFunction          = argv[4];  // "cubicSpline" or "spiky"
    std::string levelFunction           = argv[5];  // only "dimensionless"
    std::string reconstructionMethod    = argv[6];  // only "marchingCubes"

    std::string inputFolder             = argv[7];  // absolute path to simulation frames
    std::string outputFolder            = argv[8];  // absolute path to where the output is to be stored

    float smoothingLength               = std::stof(argv[9]);
    float compactSupport                = std::stof(argv[10]);
    float isoValue                      = std::stof(argv[11]);

    int numCellsInLargestAxis           = std::stoi(argv[12]);

    // Create correct reader.
    std::shared_ptr<particleReader> particleIn;
    if (inputFileFormat == "bgeo") {
        particleIn.reset(new partioParticleReader);
    } else if (inputFileFormat == "vtk") {
        particleIn.reset(new vtkParticleReader);
    } else {
        throw std::runtime_error("Input file format not supported. Has to be bgeo or vtk, but is " + inputFileFormat + ".");
    }

    // Create correct writer.
    std::shared_ptr<triangleWriter> triangleOut;
    if (outputFileFormat == "ply") {
        triangleOut.reset(new plyTriangleWriter);
    } else if (outputFileFormat == "vtk") {
        triangleOut.reset(new vtkTriangleWriter);
    } else {
        throw std::runtime_error("Output file format not supported. Has to be ply or vtk, but is " + outputFileFormat + ".");
    }

    // Create pointer to the correct neighborhood search object.
    std::shared_ptr<compactNeighborhoodSearch> nSearchPointer;
    if (neighborhoodSearch == "spatialHashing") {
        nSearchPointer.reset(new spatialHashingNeighborhoodSearch);
    } else {
        throw std::runtime_error("Neighborhood search not supported. Has to be spatialHashing, but is " + neighborhoodSearch + ".");
    }

    // Create pointer to the correct SPH interpolation kernel.
    std::shared_ptr<cubicSplineKernel> kernelPointer;
    if (kernelFunction == "cubicSpline") {
        kernelPointer.reset(new cubicSplineKernel);
    } else if (kernelFunction == "spiky") {
//        kernelPointer.reset(new spikyKernel);
    } else {
        throw std::runtime_error("Kernel function type not supported. Has to be cubicSpline or spiky, but is " + kernelFunction + ".");
    }

    // Create pointer to the correct level set function.
    std::shared_ptr<levelSetFunction> levelSetPointer;
    if (levelFunction == "dimensionless") {
        levelSetPointer.reset(new dimensionlessLevelSetFunction);
    } else {
        throw std::runtime_error("Level set function type not supported. Has to be dimensionless, but is " + levelFunction + ".");
    }

    // Create pointer to the correct reconstructor.
    std::shared_ptr<surfaceReconstructor> reconstructionPointer;
    if (reconstructionMethod == "marchingCubes") {
        reconstructionPointer.reset(new marchingCubesReconstructor);
    } else {
        throw std::runtime_error("Surface reconstruction method not supported. Has to be marchingCubes, but is " + reconstructionMethod + ".");
    }

    std::vector<std::string> inputFileNames;
    for (const auto & entry : std::experimental::filesystem::directory_iterator(inputFolder)) {
        inputFileNames.push_back(entry.path());
    }

#pragma omp parallel for firstprivate(particleIn, triangleOut, reconstructionPointer, nSearchPointer, kernelPointer, levelSetPointer)
    for (int fileNumber = 0; fileNumber < inputFileNames.size(); ++fileNumber) {
        // Read in the input file.
        std::string numThreads = std::to_string(omp_get_num_threads());
        std::string threadNum = std::to_string(omp_get_thread_num());
        std::string inputFile = inputFileNames[fileNumber];
        if (inputFileFormat == "vtk" && inputFile.substr(inputFile.size()-3, inputFile.size()) == "vtk" ||
            inputFileFormat == "bgeo" && inputFile.substr(inputFile.size()-4, inputFile.size()) == "bgeo") {
            // Get file names.
            int fileNameBeginning = inputFile.find_last_of("/");
            int fileNameEnding = inputFile.find_last_of(".");
            std::string fileEnding = (outputFileFormat == "vtk") ? ".vtk" : ".ply";
            std::string outputFile = outputFolder + inputFile.substr(fileNameBeginning, fileNameEnding) + fileEnding;
            if (std::experimental::filesystem::exists(outputFile)) {
                throw std::runtime_error("Thread " + threadNum + " of " + numThreads + ": File " + outputFile + " already exists.");
            }

            // Read in particles.
            std::cout << "Thread " + threadNum + " of " + numThreads + ": reading " << inputFile << std::endl;
            particleList particles = particleIn->read(inputFile);

            // Reconstruct a surface using marching cubes algorithm.
            graph reconstructionGraph(particles, numCellsInLargestAxis);
            triangleList result = reconstructionPointer->reconstruct(
                reconstructionGraph, particles, smoothingLength, compactSupport, isoValue, levelSetPointer, nSearchPointer, kernelPointer);

            // Write the output file.
            std::cout << "Thread " + threadNum + " of " + numThreads + ": writing to " << outputFile << std::endl;
            triangleOut->write(outputFile, result);
        } else {
            std::cerr << "Thread " + threadNum + " of " + numThreads + ": File " << inputFile << " is of wrong format." << std::endl;
        }
    }

    particleIn.reset();
    triangleOut.reset();
    reconstructionPointer.reset();
    levelSetPointer.reset();
    nSearchPointer.reset();
    kernelPointer.reset();
    return 0;
}
