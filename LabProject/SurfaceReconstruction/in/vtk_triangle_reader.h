#ifndef VTK_TRIANGLE_READER_H
#define VTK_TRIANGLE_READER_H

#include <string>

#include "triangle_reader.h"

/** \class vtkTriangleReader
 * \brief Class handling the reading of triangles from the file format vtk
 * \details This class reads the triangle data from vtk files given by their file name.
 */
class vtkTriangleReader : public triangleReader {
  public:
    vtkTriangleReader();

    /** \brief Function where the actual reading triangles algorithm from vtk files is implemented
     * \details This function converts a file of the format vtk to the data structure triangleList
     *  using the external library VTKStream.
     * \param filename name of the vtk file with the triangles to read in
     */
    triangleList read(const std::string &filename);
};

#include "vtk_triangle_reader.cpp"

#endif // VTK_TRIANGLE_READER_H
