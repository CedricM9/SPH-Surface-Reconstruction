#pragma once

#include "particle_reader.hpp"

class vtkParticleReader : public particleReader {
  public:
    vtkParticleReader();

    particleList read(std::string filename);
};

#include "vtk_particle_reader.cpp"
