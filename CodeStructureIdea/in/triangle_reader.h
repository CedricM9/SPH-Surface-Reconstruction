#ifndef TRIANGLE_READER_H
#define TRIANGLE_READER_H

#include <string>

#include "reader.h"

/** \class triangleReader
 * \brief Class handling the reading of different file formats for triangles
 * \details This abstract class incorporates the structure common to all classes reading triangle files in:
 *  vtkTriangleReader implement the file format vtk.
 */
class triangleReader : public reader {
  public:
    triangleReader() {}

    /** \brief Abstract function where the actual reading triangles algorithm is implemented in the derived classes
     * \param filename name of the file with the triangles to read in
     */
    virtual particleList read(std::string filename) = 0;
};

#endif // TRIANGLE_READER_H
