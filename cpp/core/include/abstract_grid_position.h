#ifndef _ABSTRACT_GRID_POSITION_H
#define _ABSTRACT_GRID_POSITION_H

#include "abstract_agent.h"

class AbstractPosition {
  public:
    virtual bool Compare(AbstractPosition *second) = 0;
};

#endif
