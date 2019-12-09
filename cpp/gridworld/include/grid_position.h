#ifndef _GRID_POSITION_H
#define _GRID_POSITION_H

#include "abstract_grid_position.h"
#include <cstdlib>


class GridDistance : public AbstractDistance {
  public:
    int delta_x;
    int delta_y;

    virtual uint32_t GetAbsolute() {
      /* Use the infinity norm */
      return std::max(delta_x, delta_y);
    }
};

class GridPosition : public AbstractPosition {
  public:
    uint32_t x;
    uint32_t y;

    GridPosition(uint32_t x_coordinate, uint32_t y_coordinate) : x(x_coordinate), y(y_coordinate) {} 

    virtual bool Compare (AbstractPosition *second) {
      GridPosition *other = dynamic_cast<GridPosition *>(second);

      return (x == other->x && y == other->y);
    }

    virtual AbstractDistance *GetDistanceFrom(AbstractPosition *pos) {
      GridPosition *my_pos = dynamic_cast<GridPosition *>(pos); 

      /* FIXME: Record this guy */
      GridDistance *distance = new GridDistance();
      distance->delta_x = std::labs((uint32_t) (my_pos->x - x));
      distance->delta_y = std::labs((uint32_t) (my_pos->y - y));

      return distance;
      

    }
};

#endif
