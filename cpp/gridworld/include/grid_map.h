#ifndef  _GRIDWORLD_MAP_H
#define _GRIDWORLD_MAP_H

#include "abstract_map.h"
#include "grid_position.h"

class GridWorldMap : AbstractMap {
  public:
    /* Generic constructr for the gridworld map. */
    GridWorldMap();
  
    /* 
     * Is the provided gridposition a valid position for this instantianted
     * grid?
     */
    bool isValidPosition(GridPosition grid_pos);
};

#endif
