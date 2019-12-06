#ifndef  _GRIDWORLD_MAP_H
#define _GRIDWORLD_MAP_H

#include "abstract_map.h"
#include "grid_position.h"
#include "grid_map_updates.h"


#include <unordered_map>

class GridWorldMap : public AbstractMap {
  private:
    /* The board's dimensions */
    uint32_t height;
    uint32_t width;

    virtual void doSeqTaggedMapUpdates(AbstractPosition *tag,\
                                         std::vector<AbstractUpdate*> &map_updates);
    
    virtual std::unordered_map<AbstractAgent *, AbstractPosition *> *getAgentMapInfo();

  public:
    /* Generic constructr for the gridworld map. */
    GridWorldMap(uint32_t awidth, uint32_t aheight) : width(awidth), height(aheight) {} 
    ~GridWorldMap() = default;
  
    /* 
     * Is the provided gridposition a valid position for this instantianted
     * grid?
     */
    bool isValidPosition(GridPosition grid_pos);

    virtual void doTaggedMapUpdates(AbstractPosition *active_position, \
                            std::vector<AbstractUpdate*> map_updates);

    /* Method to register agent. */
    virtual void RegisterAgent(AbstractAgent *agent, AgentMethod method);
};



#endif
