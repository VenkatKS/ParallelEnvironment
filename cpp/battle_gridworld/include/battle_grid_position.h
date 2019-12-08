#ifndef _BATTLE_GRID_POSITION_H
#define _BATTLE_GRID_POSITION_H

#include "abstract_grid_position.h"
#include <cstdlib>


class BattleGridDistance : public AbstractDistance {
  public:
    int delta_x;
    int delta_y;

    virtual uint32_t GetAbsolute() {
      /* Use the infinity norm */
      return std::max(delta_x, delta_y);
    }
};

class BattleGridPosition : public AbstractPosition {
  public:
    uint32_t x;
    uint32_t y;
    
    /* The simple position is just initialized with the x, and y coors */
    BattleGridPosition(uint32_t x_coordinate, uint32_t y_coordinate):\
      x(x_coordinate), y(y_coordinate) {} 

    virtual bool Compare (AbstractPosition *second) { 
      BattleGridPosition *other = dynamic_cast<BattleGridPosition *>(second);

      return (x == other->x && y == other->y);
    }

    virtual AbstractDistance *GetDistanceFrom(AbstractPosition *pos) {
      BattleGridPosition *my_pos = dynamic_cast<BattleGridPosition *>(pos);

      /* FIXME: Register this guy */
      BattleGridDistance *distance = new BattleGridDistance();
      distance->delta_x = std::labs((uint32_t) (my_pos->x - x));
      distance->delta_y = std::labs((uint32_t) (my_pos->y - y));
      return distance;
    }

    
};

#endif

