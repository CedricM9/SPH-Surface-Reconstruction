#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Tools/Smoother/JacobiLaplaceSmootherT_impl.hh>
#include <OpenMesh/Tools/Decimater/DecimaterT.hh>
#include <OpenMesh/Tools/Decimater/ModQuadricT.hh>

typedef OpenMesh::Smoother::JacobiLaplaceSmootherT<MyMesh> Smoother;
typedef OpenMesh::Decimater::DecimaterT<MyMesh> Decimater;
typedef OpenMesh::Decimater::ModQuadricT<MyMesh>::Handle HModQuadric;
typedef OpenMesh::IO::ExporterT<MyMesh> Bexporter;

openMeshProcessor::openMeshProcessor() {}

triangleList openMeshProcessor::smooth(const triangleList& list, int smoothingTimes) const {
    // Convert triangleList to the OpenMesh data structure.
    MyMesh mesh = getMeshFromTriangleList(list);

    // Apply OpenMesh smoothing algorithm.
    Smoother meshSmoother(mesh);
    meshSmoother.initialize(Smoother::Tangential, Smoother::C2);
    meshSmoother.smooth(smoothingTimes);

    // Convert mesh from the OpenMesh data structure back to triangleList.
    triangleList smoothedList = getTriangleListFromMesh(mesh);
    return smoothedList;
}

triangleList openMeshProcessor::simplify(const triangleList& list) const {
    // Convert triangleList to the OpenMesh data structure.
    MyMesh mesh = getMeshFromTriangleList(list);
    mesh.request_vertex_status();
    
    // Get an iterator over all halfedges.
    MyMesh::HalfedgeIter he_it, he_end=mesh.halfedges_end();

    // If halfedge is boundary, lock the corresponding vertices.
    for (he_it = mesh.halfedges_begin(); he_it != he_end ; ++he_it) {
        if (mesh.is_boundary(*he_it)) {
            mesh.status(mesh.to_vertex_handle(*he_it)).set_locked(true);
            mesh.status(mesh.from_vertex_handle(*he_it)).set_locked(true);
        }
    }

    // Create a decimater object connected to the mesh and register a quadric module.
    Decimater decimater(mesh);
    HModQuadric hModQuadric;
    decimater.add(hModQuadric);

    // Execute the decimation algorithm.
    decimater.module(hModQuadric).unset_max_err();
    decimater.initialize();
    decimater.decimate();

    // Remove decimated elements from the mesh.
    mesh.garbage_collection();

    // Convert mesh from the OpenMesh data structure back to triangleList.
    triangleList simplifiedList = getTriangleListFromMesh(mesh);
    return simplifiedList;
}

MyMesh openMeshProcessor::getMeshFromTriangleList(const triangleList& list) const {
    MyMesh mesh;

    // Add vertices to the mesh.
    for (int i=0; i<list.getNumberOfParticles(); ++i) {
        particle p = list.getParticle(i);
        mesh.add_vertex(MyMesh::Point(p.x(), p.y(), p.z()));
    }

    // Add faces to the mesh.
    std::vector<MyMesh::VertexHandle> face_vhandles;
    for (int i=0; i<list.getNumberOfTriangles(); ++i) {
        face_vhandles.clear();
        std::array<int, 3> triangle_indices = list.getTriangleIndices(i);
        for (int j=0; j<3; ++j) {
            face_vhandles.push_back(MyMesh::VertexHandle(triangle_indices[j]));
        }
        mesh.add_face(face_vhandles);
    }

    return mesh;
}

triangleList openMeshProcessor::getTriangleListFromMesh(const MyMesh& mesh) const {
    triangleList list;

    // Add vertices to the triangle list.
    for (auto v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
        list.addParticle(mesh.point(*v_it)[0], mesh.point(*v_it)[1], mesh.point(*v_it)[2]);
    }

    // Add faces to the triangle list.
    Bexporter exporter(mesh);
    std::vector<MyMesh::VertexHandle> vhandles;
    for (size_t i = 0; i < exporter.n_faces(); ++i) { 
        vhandles.clear();
        exporter.get_vhandles(MyMesh::FaceHandle(int(i)), vhandles); 
        list.addTriangle(vhandles[0].idx(), vhandles[1].idx(), vhandles[2].idx());
    } 

    return list;
}

