particleList::particleList() {}
    
void particleList::addParticle(float x, float y, float z) {
    particles_.push_back(particle(x,y,z));
}

void particleList::addParticle(particle p) {
    particles_.push_back(p);
}

void particleList::removeParticle() {
    particles_.pop_back();
}

particle& particleList::getParticle(int index) {
    return particles_[index];
}

particle particleList::getParticle(int index) const {
    return particles_[index];
}

int particleList::getNumberOfParticles() const {
    return particles_.size();
}

std::vector<std::array<float, 3>> particleList::getParticleVector() const {
    std::vector<std::array<float, 3>> particleVector;
    for (int i=0; i<particles_.size(); ++i) {
        particleVector.push_back(particles_[i].getArray());
    }
    return particleVector;
}

