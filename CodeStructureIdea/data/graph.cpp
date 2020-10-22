graph::graph() : xMin_(0.0), xMax_(0.0), yMin_(0.0), yMax_(0.0), zMin_(0.0), zMax_(0.0), cellSize_(0.0) {}

graph::graph(float x1, float x2, float y1, float y2, float z1, float z2)
        : xMin_(x1), xMax_(x2), yMin_(y1), yMax_(y2), zMin_(z1), zMax_(z2), cellSize_(0.0) {}

float const& graph::xMin() const {
    return xMin_;
}

float const& graph::xMax() const {
    return xMax_;
}

float const& graph::yMin() const {
    return yMin_;
}

float const& graph::yMax() const {
    return yMax_;
}

float const& graph::zMin() const {
    return zMin_;
}

float const& graph::zMax() const {
    return zMax_;
}


float const& graph::cellSize() const {
    return cellSize_;
}

int numCells(int i) {
    return numCells_[i];
}


void adjustCellSize(float val) {
    cellSize_ = val;
    numCells_[0] = (xMax_ - xMin_) / cellSize_;
    numCells_[1] = (yMax_ - yMin_) / cellSize_;
    numCells_[2] = (zMax_ - zMin_) / cellSize_;
}
