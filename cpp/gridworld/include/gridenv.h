#ifndef _GRID_ENV_H
#define _GRID_ENV_H

#include "abstract_env.h"
#include "abstract_map.h"
#include "grid_map.h"
#include "gridagent.h"

#include <vector>

class GridEnv : public AbstractEnv {
  public:
    /*
     * Create an instance of the GridMap environment with the provided
     * width, height, and with the specified number of environments. There 
     * will be width*height number of positions within the GridEnv.
     */
    GridEnv(uint32_t width, uint32_t height, uint32_t agents);

    virtual AbstractMap *getCurrentMap();
    virtual std::vector<AbstractAgent *> getAgents();
    virtual uint64_t getAgentRewards(AbstractAgent *agent);
    virtual bool isTerminal();

  private:
    /* The current map allocation that's running */
    GridWorldMap *active_map;
    /* The list of currently registered agents */
    std::vector<AbstractAgent *> agent_list;
};


#endif
