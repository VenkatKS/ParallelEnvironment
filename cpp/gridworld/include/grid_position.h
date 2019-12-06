#ifndef _GRID_POSITION_H
#define _GRID_POSITION_H

#include "abstract_grid_position.h"

class GridPosition : public AbstractPosition {
  public:
    uint32_t x;
    uint32_t y;

    GridPosition(uint32_t x_coordinate, uint32_t y_coordinate) : x(x_coordinate), y(y_coordinate) {} 

    virtual bool Compare (AbstractPosition *second) {
      GridPosition *other = dynamic_cast<GridPosition *>(second);

      return (x == other->x && y == other->y);
    }
};

#endif
