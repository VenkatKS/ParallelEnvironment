#ifndef _BATTLE_GRID_POSITION_H
#define _BATTLE_GRID_POSITION_H

#include "abstract_grid_position.h"

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
};

#endif

