#ifndef PLY_TRIANGLE_WRITER_H
#define PLY_TRIANGLE_WRITER_H

#include "triangle_writer.h"

/** \class plyTriangleWriter
 * \brief Class handling the writing of triangle lists to the file format ply
 * \details This class writes triangle lists to ply files specified by the file names.
 */
class plyTriangleWriter : public triangleWriter {
  public:
    plyTriangleWriter();

    /** \brief Funtion where the actual writing triangles algorithm to ply files is implemented
     * \details This function converts a given triangle list to the file format ply using the external
     *  library happly.
     * \param filename name of the ply file to write the particles to
     * \param list triangle list to write to the specified file
     */
    void write(const std::string& filename, const particleList& list);
};

#include "ply_triangle_writer.cpp"

#endif // PLY_TRIANGLE_WRITER_H
