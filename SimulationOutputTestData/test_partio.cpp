#include <Partio.h>
#include <iostream>
#include <string>

int main() {

    std::string file_name = "partio/ParticleData_Fluid_163.bgeo";
    Partio::ParticlesDataMutable* data = Partio::read(file_name.c_str());
    std::cout << "Number of particles " << data->numParticles() << std::endl;

    for (int i=0; i < data->numAttributes(); i++) {
        Partio::ParticleAttribute attr;
        data->attributeInfo(i,attr);
        std::cout << "attribute[" << i <<"] is " << attr.name << std::endl;
    }

    Partio::ParticleAttribute posAttr;
    if (!data->attributeInfo("position", posAttr)
        || (posAttr.type != Partio::FLOAT && posAttr.type != Partio::VECTOR) || posAttr.count != 3) {
    std::cerr << "Failed to get proper position attribute" << std::endl;
    }

    float avg[3] = {0,0,0};

    for (int i=0; i<data->numParticles(); i++) {
        const float *pos = data->data<float>(posAttr, i);
        for (int k=0; k<3; k++) avg[k] += pos[k];
    }

    for (int k=0; k<3; k++) avg[k] /= data->numParticles();
    std::cerr << "avg\t" << avg[0] << "\t" << avg[1] << "\t" << avg[2] << std::endl;

    float max[3] = {0,0,0};
    float min[3] = {0,0,0};
    int max_index[3] = {0,0,0};
    int min_index[3] = {0,0,0};

    Partio::ParticlesData& cdata = *data;
    Partio::ParticlesDataMutable::const_iterator particle_iterator = cdata.begin();
    Partio::ParticleAccessor accessor(posAttr);
    particle_iterator.addAccessor(accessor);
    for ( ; particle_iterator != cdata.end(); ++particle_iterator) {
        int index = particle_iterator.index;
        const Partio::Data<float,3>& pos = accessor.data<Partio::Data<float,3>>(particle_iterator);
        for (int k=0; k<3; ++k) {
            if (pos[k] > max[k] || index == 0) {
                max[k] = pos[k];
                max_index[k] = index;
            }
            if (pos[k] < min[k] || index == 0) {
                min[k] = pos[k];
                min_index[k] = index;
            }
        }
    }
    std::cerr << "max\t" << max[0] << "\t" << max[1] << "\t" << max[2] << std::endl;
    std::cerr << "min\t" << min[0] << "\t" << min[1] << "\t" << min[2] << std::endl;
    std::cerr << "max indices\t" << max_index[0] << " " << max_index[1] << " " << max_index[2] << std::endl;
    std::cerr << "min indices\t" << min_index[0] << " " << min_index[1] << " " << min_index[2] << std::endl;

    data->release();

}
