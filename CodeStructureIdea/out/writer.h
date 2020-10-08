#ifndef WRITER_H
#define WRITER_H

#include <string>

#include "particle_list.h"

/** \class writer
 * \brief Class handling the writing of particle lists to different file formats
 * \details This abstract class incorporates the structure common to all classes writing to files:
 *         particle and triangle lists to different file formats.
 */
class writer {
  public:
    writer() {}

    /** \brief Abstract funtion where the actual writing algorithm is implemented in the derived classes
     * \param filename name of the file to write the data to
     * \param list triangle list to write to the specified file
     */
    // TODO: should be particle list.
    virtual void write(const std::string& filename, const particleList& list) = 0;
};

#endif // WRITER_H
