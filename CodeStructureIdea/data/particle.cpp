particle::particle(double x, double y, double z) : x_(x), y_(y), z_(z) {}

double& particle::x() {
    return x_;
}

double& particle::y() {
    return y_;
}

double& particle::z() {
    return z_;
}

