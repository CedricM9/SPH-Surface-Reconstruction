#ifndef OPEN_MESH_PROCESSOR_H
#define OPEN_MESH_PROCESSOR_H

#include "post_processor.h"

#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
typedef OpenMesh::PolyMesh_ArrayKernelT<> MyMesh;


class openMeshProcessor : public postProcessor {
  public:
    openMeshProcessor();

    triangleList smooth(const triangleList& list) const;
    triangleList simplify(const triangleList& list) const;

  private:
    MyMesh getMeshFromTriangleList(const triangleList& list) const;
    triangleList getTriangleListFromMesh(const MyMesh& mesh) const;
};

#include "open_mesh_processor.cpp"

#endif // OPEN_MESH_PROCESSOR_H
