#ifndef PLY_TRIANGLE_READER_H
#define PLY_TRIANGLE_READER_H

#include <string>

#include "triangle_reader.h"

/** \class plyTriangleReader
 * \brief Class handling the reading of triangle lists from the file format ply
 * \details This class reads triangle lists from ply files specified by the file name.
 */
class plyTriangleReader : public triangleReader {
  public:
    plyTriangleReader();

    /** \brief Function where the actual reading triangles algorithm from ply files is implemented
     * \details This function converts the file format ply to a triangle list using the external
     *  library happly.
     * \param filename name of the ply file with the triangles to read in
     */
    triangleList read(const std::string &filename);
};

#include "ply_triangle_reader.cpp"

#endif // PLY_TRIANGLE_READER_H
