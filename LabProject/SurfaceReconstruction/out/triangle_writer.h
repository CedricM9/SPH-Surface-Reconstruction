#ifndef TRIANGLE_WRITER_H
#define TRIANGLE_WRITER_H

#include <string>

#include "writer.h"

/** \class triangleWriter
 * \brief Class handling the writing of triangle lists to different file formats
 * \details This abstract class incorporates the structure common to all classes writing triangle lists to files:
 *         plyTriangleWriter and vtkTriangleWriter implement the file formats ply and vtk.
 */
class triangleWriter : public writer {
  public:
    triangleWriter() {}
    virtual ~triangleWriter() = default;

    /** \brief Abstract function where the actual writing triangles algorithm is implemented in the derived classes
     * \param filename name of the file to write the triangles to
     * \param list triangle list to write to the specified file
     */
    virtual void write(const std::string& filename, const particleList& list) = 0;
};

#endif // TRIANGLE_WRITER_H
