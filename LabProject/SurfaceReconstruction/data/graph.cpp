#include <cmath>

graph::graph() : xMin_(0.0), xMax_(0.0), yMin_(0.0), yMax_(0.0), zMin_(0.0), zMax_(0.0), cellSize_(0.0) {}

//graph::graph(float x1, float x2, float y1, float y2, float z1, float z2)
//        : xMin_(x1), xMax_(x2), yMin_(y1), yMax_(y2), zMin_(z1), zMax_(z2), cellSize_(0.0) {}

graph::graph(particleList& particles, int numCellsInAxis) {
    
    xMin_ = 0.0, xMax_ = 0.0, yMin_ = 0.0, yMax_ = 0.0, zMin_ = 0.0, zMax_ = 0.0;
    
    for(int i=0; i<particles.getNumberOfParticles(); i++) {
        if(particles.getParticle(i).x() < xMin_) {xMin_ = particles.getParticle(i).x();}
        if(particles.getParticle(i).x() > xMax_) {xMax_ = particles.getParticle(i).x();}

        if(particles.getParticle(i).y() < yMin_) {yMin_ = particles.getParticle(i).y();}
        if(particles.getParticle(i).y() > yMax_) {yMax_ = particles.getParticle(i).y();}

        if(particles.getParticle(i).z() < zMin_) {zMin_ = particles.getParticle(i).z();}
        if(particles.getParticle(i).z() > zMax_) {zMax_ = particles.getParticle(i).z();}
    }
    
    float largestSide = xMax_ - xMin_;
    if((yMax_ - yMin_) > largestSide) {largestSide = yMax_ - yMin_;}
    if((zMax_ - zMin_) > largestSide) {largestSide = zMax_ - zMin_;}

    float padding = largestSide*0.1;

    xMin_ = xMin_ - padding;
    xMax_ = xMax_ + padding;
    yMin_ = yMin_ - padding;
    yMax_ = yMax_ + padding;
    zMin_ = zMin_ - padding;
    zMax_ = zMax_ + padding;

    cellSize_ = (largestSide + 2.0*padding) / (numCellsInAxis);
       
    numCells_[0] = ceil((xMax_ - xMin_) / cellSize_);
    numCells_[1] = ceil((yMax_ - yMin_) / cellSize_);
    numCells_[2] = ceil((zMax_ - zMin_) / cellSize_);
}
    


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

int graph::numCells(int i) {
    assert(i>=0 && i<3);
    return numCells_[i];
}

/*
void graph::adjustCellSize(float val) {
    cellSize_ = val;
    numCells_[0] = (xMax_ - xMin_) / cellSize_;
    numCells_[1] = (yMax_ - yMin_) / cellSize_;
    numCells_[2] = (zMax_ - zMin_) / cellSize_;
}
*/
