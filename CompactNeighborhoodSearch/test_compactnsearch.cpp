#include "CompactNSearch.h"
#include <iostream>
#include <iomanip>

using namespace CompactNSearch;

int main() {
    Real radius = 4.0;

    // Create data structure to perform neighborhood search with fixed radius.
    NeighborhoodSearch nsearch(radius);

    // Create test data.
    std::vector<std::array<Real, 3>> positions;
    int n = 30;
    // Fill vector with 3 * n real numbers representing three-dimensional point positions.
    for (int i=0; i<n; ++i) {
        std::array<Real, 3> point = {i*0.3+1.0, n-0.4*i+3.0, 5.0*n/(i+1.0)};
        positions.push_back(point);
    }

    // Add the created points to the neighborhood search data structure.
    unsigned int point_set_id = nsearch.add_point_set(positions.front().data(), positions.size());

    // Perform nerighborhood search on the added point set.
    nsearch.find_neighbors();

    // Access the neighborhood information.
    PointSet const& ps = nsearch.point_set(point_set_id);
    for (int i = 0; i < ps.n_points(); ++i) {
        std::vector<int> neighbors;
	for (size_t j = 0; j < ps.n_neighbors(point_set_id, i); ++j) {
    	    // Return the point id of the jth neighbor of the ith particle in the 0th point set.
	    const unsigned int pid = ps.neighbor(0, i, j);
            neighbors.push_back(pid);
        }
        int width = 7;
        int digits = 3;
        std::cout << std::setprecision(digits);
        std::cout << std::fixed;
        std::cout << "particle " << std::setw(2) << i << " at ";
        std::cout << std::setw(width) << positions[i][0] << ", " << std::setw(width) << positions[i][1] << ", "
                  << std::fixed << std::setw(width) << positions[i][2]
                  << " has " << std::setw(2) << neighbors.size() << " neighbors: ";
        for (int j = 0; j < neighbors.size(); ++j) {
            std::cout << neighbors[j] << ((j != neighbors.size()-1) ? ", " : "");
        }
        std::cout << std::endl;
    }

    return 0;
}
