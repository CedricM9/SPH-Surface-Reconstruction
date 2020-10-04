openMeshProcessor::openMeshProcessor() {}

triangleList openMeshProcessor::smooth(triangleList list) const {
    MyMesh mesh = getMeshFromTriangleList(list);.
    // TODO: implement smoothing algorithm
    return list;
}

triangleList openMeshProcessor::simplify(triangleList list) const {
    // TODO: implement mesh decimation algorithm.
    return list;
}

MyMesh openMeshProcessor::getMeshFromTriangleList(triangleList list) const {
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

