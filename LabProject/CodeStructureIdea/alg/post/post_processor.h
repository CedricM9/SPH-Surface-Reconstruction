#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include "CodeStructureIdea/data/triangle_list.h"

/** \class postProcessor
 * \brief Class to postprocess triangle meshes
 * \details This abstract class defines the common structure of all classes postprocessing triangle meshes:
 *  a smoothing and a mesh decimation algorithm.
 */
class postProcessor {
  public:
    postProcessor() {}

    /** \brief Abstract function where the actual smoothing algorithm is implemented in the derived classes
     * \param list triangle list to be smoothed
     * \param smoothingTimes number of times the smoothing algorithm is applied to the mesh
     */
    virtual triangleList smooth(const triangleList& list, int smoothingTimes) const = 0;

    /** \brief Abstract function where the actual mesh decimation algorithm is implemented in the derived classes
     * \param list triangle list to be simplified
     */
    virtual triangleList simplify(const triangleList& list) const = 0;
};

#endif // POST_PROCESSOR_H
