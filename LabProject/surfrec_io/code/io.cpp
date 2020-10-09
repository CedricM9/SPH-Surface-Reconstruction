#include "io.h"

std::vector<Vector3f> io::read_particles_from_vtk(const std::string path)
{
	constexpr float MAX_FLOAT = std::numeric_limits<float>::max();
	Eigen::AlignedBox3f empty_aabb;
	empty_aabb.setEmpty();
	return io::read_particles_from_vtk(path, empty_aabb, 0.0f);
}

std::vector<Vector3f> io::read_particles_from_vtk(const std::string path, const Eigen::AlignedBox3f& aabb, const float ghost_distance)
{
    //double t0 = omp_get_wtime();
	std::cout << "io::read_from_vtk started... ";

	vtkio::VTKStream vtk_stream;
	vtk_stream.read(path);
	vtk_stream.points.castInplace<float>();
	std::vector<Vector3f> particles(vtk_stream.getNumberOfPoints());
	vtk_stream.getPointsNestedIterator(particles.begin(), particles.end(), 3);

	std::vector<Vector3f> particles_in_AABB;
	if (aabb.isEmpty()) {
		particles_in_AABB = std::move(particles);
	}
	else {
		const float ghost_distance_squared = ghost_distance * ghost_distance;
		for (auto& particle : particles) {
			if (aabb.squaredExteriorDistance(particle) <= ghost_distance_squared) {
				particles_in_AABB.push_back(particle);
			}
		}
	}

    //double t1 = omp_get_wtime();
    std::cout << "finished."  << std::endl;

	if (particles_in_AABB.size() == 0) {
		std::cout << "Warning: No particles loaded intersect with the AABB domain." << std::endl;
		exit(-1);
	}

	return particles_in_AABB;
}

/*std::vector<Vector3f> io::read_particles_from_bgeo(const std::string path)
{
	constexpr float MAX_FLOAT = std::numeric_limits<float>::max();
	Eigen::AlignedBox3f empty_aabb;
	empty_aabb.setEmpty();
	return io::read_particles_from_bgeo(path, empty_aabb, 0.0f);
}

std::vector<Vector3f> io::read_particles_from_bgeo(const std::string path, const Eigen::AlignedBox3f& aabb, const float ghost_distance)
{
    double t0 = omp_get_wtime();
	std::cout << "io::read_from_bgeo started... ";


	Partio::ParticlesDataMutable* data = Partio::read(path.c_str());

	// this happens in case of invalid filenames
	if (!data) {
		std::cout << "PSR Error: Partio::read(" << path << ") returned invalid pointer" << std::endl;
		exit(-1);
	}

	// we need to get the index to read the positions
	unsigned int posIndex = 0xffffffff;
	// there might be multiple attributes associated with the particles
	// e.g. velocity, color, temperature..
	for (int i = 0; i < data->numAttributes(); i++) {
		Partio::ParticleAttribute tmp_attr;
		data->attributeInfo(i, tmp_attr);
		if (tmp_attr.name == "position")
			posIndex = i; // found it!
	}
	if (posIndex == 0xffffffff) {
		// didn't find positions
		std::cout << "PSR Error: Couldn't find the attribute 'position' in " << path << std::endl;
		exit(-1);
	}

	// the handle to the position attribute
	Partio::ParticleAttribute position_handle;
	data->attributeInfo(posIndex, position_handle);

	// If the file has no particles it is considered a failure
	if (data->numParticles() == 0) {
		std::cout << "PSR Error: File " << path << " contains no particles." << std::endl;
		exit(-1);
	}

	// Create the particles
	std::vector<Vector3f> particles;
	if (aabb.isEmpty()) {
		for (size_t particle_i = 0; particle_i < data->numParticles(); particle_i++) {
			const float* pos = data->data<float>(position_handle, particle_i);
			particles.push_back(Vector3f(pos[0], pos[1], pos[2]));
		}
	}
	else {
		const float ghost_distance_squared = ghost_distance * ghost_distance;
		for (size_t particle_i = 0; particle_i < data->numParticles(); particle_i++) {
			const float* pos = data->data<float>(position_handle, particle_i);
			Vector3f particle = Vector3f(pos[0], pos[1], pos[2]);
			if (aabb.squaredExteriorDistance(particle) <= ghost_distance_squared) {
				particles.push_back(particle);
			}
		}
	}

    double t1 = omp_get_wtime();
    std::cout << "finished.  " << t1 - t0 << " s." << std::endl;
	return particles;
} */

void io::write_trimesh_to_vtk(const std::string path, const std::vector<Vector3f>& vertices, const std::vector<std::array<int, 3>>& triangles)
{
	vtkio::VTKStream vtk_stream;
	vtk_stream.setPointsNestedIterator(vertices.begin(), vertices.end());
	vtk_stream.setCellsNestedIterator(triangles.begin(), triangles.end(), vtkio::tables::CellType::Triangle);
	vtk_stream.write(path);
}

void io::write_trimesh_to_ply(const std::string path, const std::vector<Vector3f>& vertices, const std::vector<std::array<int, 3>>& triangles)
{
	// Note: This is hand writen to be able to use float and int, and to avoid copying data unnecessarily

	// Create an empty object
	happly::PLYData plyOut;

	// Vertices
	{
		// Create the element
		std::string vertexName = "vertex";
		plyOut.addElement(vertexName, vertices.size());

		// De-interleave
		std::vector<float> xPos(vertices.size());
		std::vector<float> yPos(vertices.size());
		std::vector<float> zPos(vertices.size());
		for (size_t i = 0; i < vertices.size(); i++) {
			xPos[i] = (float)vertices[i][0];
			yPos[i] = (float)vertices[i][1];
			zPos[i] = (float)vertices[i][2];
		}

		// Store
		plyOut.getElement(vertexName).addProperty<float>("x", xPos);
		plyOut.getElement(vertexName).addProperty<float>("y", yPos);
		plyOut.getElement(vertexName).addProperty<float>("z", zPos);
	}

	// Faces
	{
		// Create the element
		std::string faceName = "face";
		plyOut.addElement(faceName, triangles.size());

		// Copy it to vector<vector<int>>. Note: I am not sure we can go around this
		std::vector<std::vector<int>> meshfaceindices;
		meshfaceindices.reserve(vertices.size());
		for (auto& triangle : triangles) {
			meshfaceindices.push_back({triangle[0], triangle[1], triangle[2]});
		}
		plyOut.getElement(faceName).addListProperty<int>("vertex_indices", meshfaceindices);
	}

	// Write the object to file
	plyOut.write(path, happly::DataFormat::Binary);
}
