#include <vector>
#include <string>

#include "../extern/Eigen/Eigen/Eigen"
//#include "../extern/partio/src/lib/Partio.h"
#include "../extern/vtkio/VTKStream.h"
#include "../extern/happly.h"
using Vector3f = Eigen::Matrix<float, 3, 1, Eigen::DontAlign>;

namespace io
{
	// Read
	std::vector<Vector3f> read_particles_from_vtk(const std::string path);
	std::vector<Vector3f> read_particles_from_vtk(const std::string path, const Eigen::AlignedBox3f& aabb, const float ghost_distance = 0.0f);
    //std::vector<Vector3f> read_particles_from_bgeo(const std::string path);
    //std::vector<Vector3f> read_particles_from_bgeo(const std::string path, const Eigen::AlignedBox3f& aabb, const float ghost_distance = 0.0f);

	// Write
	void write_trimesh_to_vtk(const std::string path, const std::vector<Vector3f>& vertices, const std::vector<std::array<int, 3>>& triangles);
	void write_trimesh_to_ply(const std::string path, const std::vector<Vector3f>& vertices, const std::vector<std::array<int, 3>>& triangles);
}

