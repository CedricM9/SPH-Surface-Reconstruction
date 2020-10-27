dimensionlessLevelSetFunction::dimensionlessLevelSetFunction() {}

double dimensionlessLevelSetFunction::evaluate(particleList& list, 
                                               particle& p, 
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

    list.addParticle(p);
    
    for(int i=0; i<list.getNumberOfParticles(); i++) {
        list.getParticle(i).setDensity(densities[i]);
    }
    
    std::vector<std::vector<int>> allNeighbors = nSearchPointer->find(list,r);
    std::vector<int> neighbors(allNeighbors[list.getNumberOfParticles()-1]);

    float result = -c;
    for(int i=0; i<neighbors.size(); i++) {
        result += (kernelPointer->evaluate(p,list.getParticle(neighbors[i]),h) / ((h*h*h)*(list.getParticle(neighbors[i]).density())));
        //result += ((evaluate(p, list.getParticle(neighbors[i]), h) / ((h*h*h) * list.getParticle(neighbors[i]).density());
    }

    list.removeParticle();

    return result;
}
