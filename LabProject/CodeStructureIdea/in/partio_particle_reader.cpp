#include <string>

#include "Partio.h"

partioParticleReader::partioParticleReader() {}

particleList partioParticleReader::read(const std::string &filename) {
    Partio::ParticlesDataMutable* data = Partio::read(filename.c_str());

    Partio::ParticleAttribute posAttr;
    if (!data->attributeInfo("position", posAttr)
        || (posAttr.type != Partio::FLOAT && posAttr.type != Partio::VECTOR) || posAttr.count != 3) {
        throw std::runtime_error("Failed to get proper position attribute in file " + filename);
    }   

    particleList list;

    for (int i=0; i<data->numParticles(); i++) {
        const float *pos = data->data<float>(posAttr, i); 
        list.addParticle(pos[0], pos[1], pos[2]);
    }

    return list;
}

