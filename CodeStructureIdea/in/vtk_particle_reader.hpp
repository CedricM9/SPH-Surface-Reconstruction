#pragma once

#include "particle_reader.hpp"

template<typename T>
class vtkParticleReader : public particleReader<T> {
  public:
    vtkParticleReader();

    particleList<T> read(std::string filename);
};

#include "vtk_particle_reader.cpp"
