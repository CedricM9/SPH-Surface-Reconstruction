#ifndef TRIANGLE_READER_H
#define TRIANGLE_READER_H

#include <string>
#include "triangle_list.h"

/** \class triangleReader
 * \brief Class handling the reading of different file formats for triangles
 * \details This abstract class incorporates the structure common to all classes reading triangle files in:
 *  vtkTriangleReader implement the file format vtk.
 */
class triangleReader {
  public:
    triangleReader() {}
    virtual ~triangleReader() = default;

    /** \brief Abstract function where the actual reading triangles algorithm is implemented in the derived classes
     * \param filename name of the file with the triangles to read in
     */
    virtual triangleList read(const std::string &filename) = 0;
};

#endif // TRIANGLE_READER_H
