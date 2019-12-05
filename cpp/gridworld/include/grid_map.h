#ifndef  _GRIDWORLD_MAP_H
#define _GRIDWORLD_MAP_H

#include "abstract_map.h"
#include "grid_position.h"
#include "grid_map_updates.h"

class GridWorldMap : public AbstractMap {
  private:
    /* The board's dimensions */
    uint32_t height;
    uint32_t width;

    void doSeqTaggedMapUpdates(GridPosition tag,\
                                         std::vector<AbstractUpdate*> map_updates);
    
    /* Not overriden from parent. Just checks the map */
    virtual bool isAgentInMap(AbstractAgent *agent);

  public:
    /* Generic constructr for the gridworld map. */
    GridWorldMap(uint32_t width, uint32_t height);
  
    /* 
     * Is the provided gridposition a valid position for this instantianted
     * grid?
     */
    bool isValidPosition(GridPosition grid_pos);
    void doTaggedMapUpdates(GridPosition active_position, \
                            std::vector<AbstractUpdate*> map_updates);
};

#endif
