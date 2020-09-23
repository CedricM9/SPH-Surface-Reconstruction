particleList::particleList() {}
    
void particleList::addParticle(double x, double y, double z) {
    particles_.push_back(particle(x,y,z));
}

void particleList::addParticle(particle p) {
    particles_.push_back(p);
}

particle const& particleList::getParticle(int index) const {
    return particles_[index];
}

int particleList::getNumberOfParticles() const {
    return particles_.size();
}

