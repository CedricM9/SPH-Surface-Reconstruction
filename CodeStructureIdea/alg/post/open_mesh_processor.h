#ifndef OPEN_MESH_PROCESSOR_H
#define OPEN_MESH_PROCESSOR_H

#include "post_processor.h"

#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
typedef OpenMesh::PolyMesh_ArrayKernelT<> MyMesh;


class openMeshProcessor : public postProcessor {
  public:
    openMeshProcessor();

    triangleList smooth(triangleList list) const;
    triangleList simplify(triangleList list) const;

  private:
    MyMesh getMeshFromTriangleList(triangleList list) const;
};

#include "open_mesh_processor.cpp"

#endif // OPEN_MESH_PROCESSOR_H
