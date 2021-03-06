#ifndef VTK_PARTICLE_READER_H
#define VTK_PARTICLE_READER_H

#include <string>

#include "particle_reader.h"

/** \class vtkParticleReader
 * \brief Class handling the reading of particles from the file format vtk
 * \details This class reads the particle data from vtk files given by their file name.
 */
class vtkParticleReader : public particleReader {
  public:
    vtkParticleReader();

    /** \brief Function where the actual reading particles algorithm from vtk files is implemented
     * \details This function converts a file of the format vtk to the data structure particleList
     *  using the external library VTKStream.
     * \param filename name of the vtk file with the particles to read in
     */
    particleList read(const std::string &filename);
};

#include "vtk_particle_reader.cpp"

#endif // VTK_PARTICLE_READER_H
