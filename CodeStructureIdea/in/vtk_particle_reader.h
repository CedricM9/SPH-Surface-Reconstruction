#ifndef VTK_PARTICLE_READER_H
#define VTK_PARTICLE_READER_H

#include "particle_reader.h"

class vtkParticleReader : public particleReader {
  public:
    vtkParticleReader();

    particleList read(std::string filename);
};

#include "vtk_particle_reader.cpp"

#endif // VTK_PARTICLE_READER_H
