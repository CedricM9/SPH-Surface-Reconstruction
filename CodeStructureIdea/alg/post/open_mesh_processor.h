#ifndef OPEN_MESH_PROCESSOR_H
#define OPEN_MESH_PROCESSOR_H

#include "post_processor.h"

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;


/** \class openMeshProcessor
 * \brief Class to postprocess triangle meshes using Open Mesh
 * \details This class implements the smoothing and mesh decimation algorithm using the library Open Mesh.
 */
class openMeshProcessor : public postProcessor {
  public:
    openMeshProcessor();

    /** \brief Function where the actual smoothing algorithm is implemented using Open Mesh
     * \details One smoothing iteration includes the calculation of the barycenter of its one-ring neighbors
     *  for each vertex and then moving the vertex to the computed barycenter.
     * \param list triangle list to be smoothed
     */
    triangleList smooth(const triangleList& list) const;

    /** \brief Function where the actual mesh decimation algorithm is implemented using Open Mesh
     * \param list triangle list to be smoothed
     */
    triangleList simplify(const triangleList& list) const;

  private:
    /** \brief Function converting the internel data structure triangleList into the Open Mesh data structure
     *  for polygon meshes
     * \param list triangle list to be converted
     */
    MyMesh getMeshFromTriangleList(const triangleList& list) const;

    /** \brief Function converting the Open Mesh data structure for polygon meshes into the internel data
     *  structure triangleList
     * \param list triangle list to be converted
     */
    triangleList getTriangleListFromMesh(const MyMesh& mesh) const;
};

#include "open_mesh_processor.cpp"

#endif // OPEN_MESH_PROCESSOR_H
