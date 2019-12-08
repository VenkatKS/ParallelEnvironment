#ifndef  _GRIDWORLD_MAP_H
#define _GRIDWORLD_MAP_H

#include "abstract_map.h"
#include "battle_grid_position.h"
#include "battle_grid_map_updates.h"

#include <unordered_map>

class BattleGridWorldMap : public AbstractMap {
  private:
    /* The board's dimensions */
    uint32_t height;
    uint32_t width;
  public:

    virtual void doSeqTaggedMapUpdates(AbstractPosition *tag,\
                                         std::vector<AbstractUpdate*> &map_updates);
    virtual AbstractPosition *getAgentMapInfo(AbstractAgent *agent);

  public:
    BattleGridWorldMap (uint32_t awidth, uint32_t aheight) : \
      BattleGridWorldMap(awidth, aheight, EnvBackend::SEQ) {} 

    /* Generic constructor for the gridworld map. */
    BattleGridWorldMap(uint32_t awidth, uint32_t aheight, EnvBackend backend) : 
        AbstractMap(backend), width(awidth), height(aheight) {} 
    ~BattleGridWorldMap() = default;
  
    /* 
     * Is the provided gridposition a valid position for this instantianted
     * grid?
     */
    bool isValidPosition(AbstractPosition *grid_pos);

    virtual void doTaggedMapUpdates(AbstractPosition *active_position, \
                            std::vector<AbstractUpdate*> map_updates);

    /* Method to register agent. */
    virtual void RegisterAgent(AbstractAgent *agent, AgentMethod method);
};



#endif
