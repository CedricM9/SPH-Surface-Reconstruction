graph::graph() : xMin(0.0), xMax(0.0), yMin(0.0), yMax(0.0), zMin(0.0), zMax(0.0), cellSize(0.0) {}

graph::graph(float x1, float x2, float y1, float y2, float z1, float z2)
        : xMin(x1), xMax(x2), yMin(y1), yMax(y2), zMin(z1), zMax(z2), cellSize(0.0) {}

float const& graph::xMin() const {
    return xMin;
}

float const& graph::xMax() const {
    return xMax;
}

float const& graph::yMin() const {
    return yMin;
}

float const& graph::yMax() const {
    return yMax;
}

float const& graph::zMin() const {
    return zMin;
}

float const& graph::zMax() const {
    return zMax;
}


float const& graph::cellSize() const {
    return cellSize;
}

int numCells(int i) {
    return numCells[i];
}


void adjustCellSize(float val) {
    cellSize = val;
    numCells[0] = (xMax - xMin) / cellSize;
    numCells[1] = (yMax - yMin) / cellSize;
    numCells[2] = (zMax - zMin) / cellSize;
}
