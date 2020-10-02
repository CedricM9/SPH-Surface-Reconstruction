particle::particel() : x_(0.0), y_(0.0), z_(0.0) {}

particle::particle(double x, double y, double z) : x_(x), y_(y), z_(z) {}

void equals(particle p) const {
    x_ = p.x();
    y_ = p.y();
    z_ = p.z();
}

double const& particle::x() const {
    return x_;
}

double const& particle::y() const {
    return y_;
}

double const& particle::z() const {
    return z_;
}

std::array<double, 3> particle::getArray() const {
    return {x_, y_, z_};
}

