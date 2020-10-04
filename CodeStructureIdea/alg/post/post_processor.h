#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include "triangle_list.h"

class postProcessor {
  public:
    postProcessor() {}

    virtual triangleList smooth(triangleList list) const = 0;
    virtual triangleList simplify(triangleList list) const = 0;
};

#endif // POST_PROCESSOR_H
