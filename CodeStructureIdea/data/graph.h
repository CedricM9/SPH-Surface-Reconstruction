#ifndef GRAPH_H
#define GRAPH_H

class graph {
    public:
        graph();
        graph(float x1, float x2, float y1, float y2, float z1, float z2);
        
        float const& xMin() const;
        float const& xMax() const;
        float const& yMin() const;
        float const& yMax() const;
        float const& zMin() const;
        float const& zMax() const;

        float const& cellSize() const;
        int cells(int i);

        void adjustCellSize(float val);

    private:
        //float xLength, yLength, zLength;
        float xMin_, xMax_;
        float yMin_, yMax_;
        float zMin_, zMax_;

        float cellSize_;
        int numCells_[3];
        



#include "graph.cpp"

#endif // GRAPH_H
