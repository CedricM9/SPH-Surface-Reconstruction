#pragma once

#include "particle_reader.h"

class vtkParticleReader : public particleReader {
  public:
    vtkParticleReader();

    particleList read(std::string filename);
};

#include "vtk_particle_reader.cpp"
