#ifndef _GRID_POSITION_H
#define _GRID_POSITION_H

#include "abstract_grid_position.h"

class GridPosition : public AbstractPosition {
  public:
    float x;
    float y;

    virtual bool Compare (AbstractPosition *second) {
      GridPosition *other = dynamic_cast<GridPosition *>(second);

      return (x == other->x && y == other->y);
    }
};

#endif
