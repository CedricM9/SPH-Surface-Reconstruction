#ifndef GRAPH_H
#define GRAPH_H

#include<cassert>

#include "particle_list.h"

class graph {
    public:
        graph ();
        graph (particleList& particles, int accuracy);
        
        float const& xMin() const;
        float const& xMax() const;
        float const& yMin() const;
        float const& yMax() const;
        float const& zMin() const;
        float const& zMax() const;

        float const& cellSize() const;
        int numCells(int i);

        //void adjustCellSize(float val);

    private:
        //float xLength, yLength, zLength;
        float xMin_, xMax_;
        float yMin_, yMax_;
        float zMin_, zMax_;

        float cellSize_;
        int numCells_[3];
        
};


#include "graph.cpp"

#endif // GRAPH_H
