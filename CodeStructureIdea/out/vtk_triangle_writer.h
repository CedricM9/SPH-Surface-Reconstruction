#ifndef VTK_TRIANGLE_WRITER_H
#define VTK_TRIANGLE_WRITER_H

#include <string>

#include "triangle_writer.h"

/** \class vtkTriangleWriter
 * \brief Class handling the writing of triangle lists to the file format vtk
 * \details This class writes triangle lists to vtk files specified by the file names.
 */
class vtkTriangleWriter : public triangleWriter {
  public:
    vtkTriangleWriter();

    /** \brief Funtion where the actual writing triangles algorithm to vtk files is implemented
     * \details This function converts a given triangle list to the file format vtk using the external
     *  library VTKStream.
     * \param filename name of the vtk file to write the particles to
     * \param list triangle list to write to the specified file
     */
    void write(const std::string& filename, const particleList& list);
};

#include "vtk_triangle_writer.cpp"

#endif // VTK_TRIANGLE_WRITER_H
