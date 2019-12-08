#include "battle_env.h"
#include "battle_grid_map.h"
#include "battle_grid_position.h"
#include "battle_grid_agent.h"


BattleEnv::BattleEnv(uint32_t width, uint32_t height, uint32_t agents, EnvBackend execution_engine)  : AbstractEnv(execution_engine)
{
    /* Generate the new map */
    active_map = new BattleGridWorldMap(width, height);

    for (int i = 0; i < agents; i++) {
      /* FIXME: Track allocation for these creations. */

      /* Create a new agent */
      BattleGridAgent *this_agent = new BattleGridAgent(active_map, \
          BattleGridAgentOrientation::UP, 100, static_cast<uint64_t>(i));

      /* Add the agent to the map by registering it and add it to our list. */
      active_map->RegisterAgent(this_agent, RANDOM);
      agent_list.push_back(this_agent);
    }

    return;
}

AbstractMap *BattleEnv::getCurrentMap() {
  return active_map;
}

std::vector<AbstractAgent *> BattleEnv::getAgents() {
  return agent_list;
}

uint64_t BattleEnv::getAgentRewards(AbstractAgent *agent) {
  BattleGridPosition *pos = dynamic_cast<BattleGridPosition *>(active_map->getAgentPosition\
            (agent));

  return ((pos->x * pos->x) + (pos->y * pos->y));
}

bool BattleEnv::isTerminal() {
  return false;
}
