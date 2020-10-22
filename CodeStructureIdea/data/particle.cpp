particle::particle() : x_(0.0), y_(0.0), z_(0.0) {}
particle::particle(float x, float y, float z) : x_(x), y_(y), z_(z) {}

particle::particle(const particle& p) : x_(p.x()), y_(p.y()), z_(p.z()) {}

/*void equals(particle p) const {
    x_ = p.x();
    y_ = p.y();
    z_ = p.z();
}*/

float const& particle::x() const {
    return x_;
}

float const& particle::y() const {
    return y_;
}

float const& particle::z() const {
    return z_;
}

std::array<float, 3> particle::getArray() const {
    return {x_, y_, z_};
}

