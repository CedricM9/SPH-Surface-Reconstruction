#ifndef READER_H
#define READER_H

#include <string>

#include "CodeStructureIdea/data/particle_list.h"

/** \class reader
 * \brief Class handling the reading of different file formats for particle lists
 * \details This abstract class incorporates the structure common to all classes reading files in:
 *         particle and triangle lists of different file formats.
 */
class reader {
  public:
    reader() {}
    virtual ~reader() = default;

    /** \brief Abstract function where the actual reading algorithm is implemented in the derived classes
     * \param filename name of the file with the data to read in
     */
    virtual particleList read(std::string filename) = 0;
};

#endif // READER_H
