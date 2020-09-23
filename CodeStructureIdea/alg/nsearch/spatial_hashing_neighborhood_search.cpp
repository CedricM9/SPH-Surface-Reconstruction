#include "CompactNSearch.h"

using namespace CompactNSearch;

spatialHashingNeighborhoodSearch::spatialHashingNeighborhoodSearch() {}

std::vector<std::vector<int>> spatialHashingNeighborhoodSearch::find(const particleList& list, double radius) {
    // TODO: implement spatial neighborhood search using CompactNSearch library.

    // Create data structure to perform neighborhood search with fixed radius.
    NeighborhoodSearch nsearch(radius);

    // Create test data.
    std::vector<std::array<Real, 3>> positions;
    int numberParticles = list.getNumberOfParticles();
    int getNumberOfParticles();
    for (int i=0; i<numberParticles; ++i) {
        std::array<Real, 3> point = {list.getParticle(i).x(), list.getParticle(i).y(), list.getParticle(i).z()};
        positions.push_back(point);
    }

    // Add the created points to the neighborhood search data structure.
    unsigned int point_set_id = nsearch.add_point_set(positions.front().data(), positions.size());

    // Perform nerighborhood search on the added point set.
    nsearch.find_neighbors();

    // Access the neighborhood information.
    PointSet const& pointSet = nsearch.point_set(point_set_id);
    std::vector<std::vector<int>> all_neighbors;
    for (int i = 0; i < pointSet.n_points(); ++i) {
        std::vector<int> neighbors;
        for (size_t j = 0; j < pointSet.n_neighbors(point_set_id, i); ++j) {
            // Return the point id of the jth neighbor of the ith particle in the 0th point set.
            const unsigned int pid = pointSet.neighbor(0, i, j);
            neighbors.push_back(pid);
        }
        all_neighbors.push_back(neighbors);
    }
    return all_neighbors;
}

