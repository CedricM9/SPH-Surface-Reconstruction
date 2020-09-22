template <typename T>
particleList<T>::particleList() {}
    
template <typename T>
void particleList<T>::addParticle(T x, T y, T z) {
    particles_.push_back(particle<T>(x,y,z));
}

template <typename T>
void particleList<T>::addParticle(particle<T> p) {
    particles_.push_back(p);
}

template <typename T>
particle<T>& particleList<T>::getParticle(int index) {
    return particles_[index];
}

