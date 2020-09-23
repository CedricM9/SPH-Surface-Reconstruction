particle::particle(double x, double y, double z) : x_(x), y_(y), z_(z) {}

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

