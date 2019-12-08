#ifndef _BATTLE_ENV_H
#define _BATTLE_ENV_H

#include "abstract_env.h"
#include "abstract_map.h"
#include "battle_grid_map.h"

#include <vector>

class BattleEnv : public AbstractEnv {
  public:
    /*
     * Create an instance of the GridMap environment with the provided
     * width, height, and with the specified number of environments. There 
     * will be width*height number of positions within the GridEnv.
     */

    /* Construction with the default sequential execution engine */
    BattleEnv(uint32_t width, uint32_t height, uint32_t agents) : 
      BattleEnv(width, height, agents, EnvBackend::SEQ) {}
    
    /* Construction with a specified backend */
    BattleEnv(uint32_t width, uint32_t height, uint32_t agents, EnvBackend 
        execution_engine);

    virtual AbstractMap *getCurrentMap();
    virtual std::vector<AbstractAgent *> getAgents();
    virtual uint64_t getAgentRewards(AbstractAgent *agent);
    virtual bool isTerminal();

  private:
    /* The currently active world map */
    BattleGridWorldMap *active_map;

    /* The list of agents currently executing on this map */
    std::vector<AbstractAgent *> agent_list;
};



#endif
