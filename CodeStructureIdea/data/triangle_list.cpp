#include <cassert>

template <typename T>
triangleList<T>::triangleList() : particleList<T>() {}
    
template <typename T>
triangleList<T>::triangleList(particleList<T> list) : particleList<T>(list) {}
    
template <typename T>
void triangleList<T>::addTriangle(int index1, int index2, int index3) {
    vertices_.push_back({index1, index2, index3});
}

template <typename T>
std::array<particle<T>, 3> triangleList<T>::getTriangle(int index) {
    assert(index < this->particles_.size());
    return std::array<particle<T>, 3>({
        this->particles_[vertices_[index][0]],
        this->particles_[vertices_[index][1]],
        this->particles_[vertices_[index][2]]
    });
}

