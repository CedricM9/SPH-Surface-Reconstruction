dimensionlessLevelSetFunction::dimensionlessLevelSetFunction() {}

double dimensionlessLevelSetFunction::evaluate(particleList& list, 
                                               float x,
                                               float y,
                                               float z,
                                               float h,
                                               float c,
                                               float r,
                                               std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                                               std::shared_ptr<SPHInterpolationKernel> kernelPointer
) {
    std::vector<float> densities;
    for(int i=0; i<list.getNumberOfParticles(); i++) {
        densities.push_back(list.getParticle(i).density());
    }
    
    std::vector<unsigned int> neighbors = nSearchPointer->find(list,r,x,y,z);

    float result = -c;
    for(int i=0; i<neighbors.size(); i++) {
        result += (kernelPointer->evaluate(x,y,z,list.getParticle(neighbors[i])) / (pow(h,3)*(list.getParticle(neighbors[i]).density())));
    }
    return result;
}
