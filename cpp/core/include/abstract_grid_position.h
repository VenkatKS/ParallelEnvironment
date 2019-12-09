#ifndef _ABSTRACT_GRID_POSITION_H
#define _ABSTRACT_GRID_POSITION_H

#include "abstract_agent.h"
#include <stdint.h>

class AbstractDistance {
  public:
    /* Quantify the distance into a single value */
    virtual uint32_t GetAbsolute() = 0;
};

class AbstractPosition {
  public:
    virtual bool Compare(AbstractPosition *second) = 0;
    virtual AbstractDistance *GetDistanceFrom(AbstractPosition *pos) = 0;
};


#endif
