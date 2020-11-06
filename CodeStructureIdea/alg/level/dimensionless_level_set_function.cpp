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
    
    std::vector<std::vector<unsigned int>> allNeighbors = nSearchPointer->find(list,r);
    std::vector<unsigned int> neighbors = allNeighbors[list.getNumberOfParticles()-1];

    //std::cout << "p: " << p.x() << " " << p.y() << " " << p.z() << std::endl;
    float result = -c;
    kernelPointer->setRadius(h);
    for(int i=0; i<neighbors.size(); i++) {
        particle cur = list.getParticle(neighbors[i]);
        float du = kernelPointer->evaluate(p,list.getParticle(neighbors[i]));
        float y = list.getParticle(neighbors[i]).density();
        //std::cout << i << " " << neighbors[i] << "; " << cur.x() << " " << cur.y() << " " << cur.z() << "; " << du << " " << y << std::endl;
        result += (kernelPointer->evaluate(p,list.getParticle(neighbors[i])) / ((h*h*h)*(list.getParticle(neighbors[i]).density())));
        //result += ((evaluate(p, list.getParticle(neighbors[i]), h) / ((h*h*h) * list.getParticle(neighbors[i]).density());
    }
    //std::cout << "---" << std::endl;

    list.removeParticle();

    return result;
}
