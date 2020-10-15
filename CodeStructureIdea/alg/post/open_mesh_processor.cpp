#include <OpenMesh/Tools/Decimater/DecimaterT.hh>
#include <OpenMesh/Tools/Decimater/ModQuadricT.hh>

typedef OpenMesh::Decimater::DecimaterT<MyMesh> Decimater;
typedef OpenMesh::Decimater::ModQuadricT<MyMesh>::Handle HModQuadric;

openMeshProcessor::openMeshProcessor() {}

triangleList openMeshProcessor::smooth(const triangleList& list) const {
    // Convert triangleList to the OpenMesh data structure.
    MyMesh mesh = getMeshFromTriangleList(list);

    // this vector stores the computed centers of gravity
    std::vector<MyMesh::Point> cogs;
    std::vector<MyMesh::Point>::iterator cog_it;
    cogs.reserve(mesh.n_vertices());

    // smoothing mesh n times
    MyMesh::VertexIter          v_it, v_end(mesh.vertices_end());
    MyMesh::VertexVertexIter    vv_it;
    MyMesh::Point               cog;
    MyMesh::Scalar              valence;
    unsigned int                i, n=3;

    for (i=0; i<n; ++i) {
        cogs.clear();
        for (v_it=mesh.vertices_begin(); v_it!=v_end; ++v_it) {
            cog[0] = cog[1] = cog[2] = valence = 0.0;
      
            for (vv_it=mesh.vv_iter( *v_it ); vv_it.is_valid(); ++vv_it) {
                cog += mesh.point( *vv_it );
                ++valence;
            }
        cogs.push_back(cog / valence);
        }
    
        for (v_it=mesh.vertices_begin(), cog_it=cogs.begin(); v_it!=v_end; ++v_it, ++cog_it) {
            if ( !mesh.is_boundary( *v_it ) ) mesh.set_point( *v_it, *cog_it );
        }
    }

    triangleList smoothedList = getTriangleListFromMesh(mesh);
    return smoothedList;
}

triangleList openMeshProcessor::simplify(const triangleList& list) const {
    // TODO: implement mesh decimation algorithm.

    MyMesh mesh = getMeshFromTriangleList(list);
    mesh.request_vertex_status();
    
    // Get an iterator over all halfedges
    MyMesh::HalfedgeIter he_it, he_end=mesh.halfedges_end();

    // If halfedge is boundary, lock the corresponding vertices
    for (he_it = mesh.halfedges_begin(); he_it != he_end ; ++he_it) {
        if (mesh.is_boundary(*he_it)) {
            mesh.status(mesh.to_vertex_handle(*he_it)).set_locked(true);
            mesh.status(mesh.from_vertex_handle(*he_it)).set_locked(true);
        }
    }

    Decimater decimater(mesh);  // a decimater object, connected to a mesh
    HModQuadric hModQuadric;    // use a quadric module
    decimater.add(hModQuadric); // register module at the decimater

    /*
     * since we need exactly one priority module (non-binary)
     * we have to call set_binary(false) for our priority module
     * in the case of HModQuadric, unset_max_err() calls set_binary(false) internally
     */
    decimater.module(hModQuadric).unset_max_err();
    decimater.initialize();
    decimater.decimate();

    // after decimation: remove decimated elements from the mesh
    mesh.garbage_collection();

    return list;
}

MyMesh openMeshProcessor::getMeshFromTriangleList(const triangleList& list) const {
    MyMesh mesh;

    MyMesh::VertexHandle vhandle[list.getNumberOfParticles()];
    for (int i=0; i<list.getNumberOfParticles(); ++i) {
        particle p = list.getParticle(i);
        vhandle[i] = mesh.add_vertex(MyMesh::Point(p.x(), p.y(), p.z()));
    }

    std::vector<MyMesh::VertexHandle> face_vhandles;
    for (int i=0; i<list.getNumberOfTriangles(); ++i) {
        face_vhandles.clear();
        std::array<int, 3> triangle_indices = list.getTriangleIndices(i);
        for (int j=0; j<3; ++j) face_vhandles.push_back(vhandle[triangle_indices[j]]);
        mesh.add_face(face_vhandles);
    }

    return mesh;
}

triangleList openMeshProcessor::getTriangleListFromMesh(const MyMesh& mesh) const {
    triangleList list;

    for (auto v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
        list.addParticle(mesh.point(*v_it)[0], mesh.point(*v_it)[1], mesh.point(*v_it)[2]);
    }

    for (auto f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
        // TODO: get triangle indices
        //list.addTriangle(mesh.face(*f_it)[0]); //[0], mesh.face(*f_it)[1], mesh.face(*f_it)[2]);
    }

    return list;
}

