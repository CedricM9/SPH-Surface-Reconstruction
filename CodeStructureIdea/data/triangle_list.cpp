#include <cassert>

triangleList::triangleList() : particleList() {}
    
triangleList::triangleList(particleList list) : particleList(list) {}
    
void triangleList::addTriangle(int index1, int index2, int index3) {
    vertices_.push_back({index1, index2, index3});
}

std::array<particle, 3> triangleList::getTriangle(int index) {
    assert(index < this->particles_.size());
    return std::array<particle, 3>({
        this->particles_[vertices_[index][0]],
        this->particles_[vertices_[index][1]],
        this->particles_[vertices_[index][2]]
    });
}

std::vector<std::vector<size_t>> triangleList::getFaceVector() const {
    std::vector<std::vector<size_t>> faceVector;
    for (int i=0; i<faceVector.size(); ++i) {
        faceVector.push_back({vertices_[i][0], vertices_[i][1], vertices_[i][2]});
    }
    return faceVector;
}

