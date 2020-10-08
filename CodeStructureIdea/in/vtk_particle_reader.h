#ifndef VTK_PARTICLE_READER_H
#define VTK_PARTICLE_READER_H

#include "particle_reader.h"

/** \class vtkParticleReader
 * \brief Class handling the reading of particles from the file format vtk
 * \details This class reads the particle data from vtk files given by their file name.
 */
class vtkParticleReader : public particleReader {
  public:
    vtkParticleReader();

    /** \brief Funtion where the actual reading particles algorithm from vtk files is implemented
     * \param filename name of the vtk file with the particles to read in
     */
    particleList read(std::string filename);
};

#include "vtk_particle_reader.cpp"

#endif // VTK_PARTICLE_READER_H
