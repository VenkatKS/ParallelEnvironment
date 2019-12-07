#include "gridenv.h"

GridEnv::GridEnv(uint32_t width, uint32_t height, uint32_t num_agents) {
  /* FIXME: Find a way to keep track of this allocation */
  active_map = new GridWorldMap(width, height);
  
  for (int i = 0; i < num_agents; i++) {
    /* FIXME: Track allocation for these creations. */

    /* Create a new agent */
    GridAgent *this_agent = new GridAgent(active_map, \
        GridAgentOrientation::UP, 100);

    /* Add the agent to the map by registering it and add it to our list. */
    active_map->RegisterAgent(this_agent, RANDOM);
    agent_list.push_back(this_agent);
  }
}

AbstractMap *GridEnv::getCurrentMap() {
  return active_map;
}

std::vector<AbstractAgent *> GridEnv::getAgents() {
  return agent_list;
}

uint64_t GridEnv::getAgentRewards(AbstractAgent *agent) {
  GridPosition *pos = dynamic_cast<GridPosition *>(active_map->getAgentPosition\
            (agent));

  return ((pos->x * pos->x) + (pos->y * pos->y));
}

bool GridEnv::isTerminal() {
  return false;
}



