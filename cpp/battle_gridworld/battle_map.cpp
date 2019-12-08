/* The concrete instantiation of MAP */

#include "battle_grid_map.h"
#include "battle_grid_position.h"
#include "logger.h"
#include "battle_grid_map_updates.h"

// #include "gridagent.h"

#include <unordered_map>

bool BattleGridWorldMap::isValidPosition(AbstractPosition *grid_position) {
  BattleGridPosition *grid_pos = dynamic_cast<BattleGridPosition*>(grid_position);

  /* Ensure the provided coordinates is within the board's height and width*/
  if (grid_pos->x < 0 || grid_pos->x >= width
          || grid_pos->y < 0 || grid_pos->y >= height) {
      return false;
  }

  return true;
}

void BattleGridWorldMap::doTaggedMapUpdates(AbstractPosition *active_position, \
    std::vector<AbstractUpdate*> map_updates) {
  doSeqTaggedMapUpdates(active_position, map_updates);
  return;
}

void BattleGridWorldMap::doSeqTaggedMapUpdates(AbstractPosition *tag,\
                                         std::vector<AbstractUpdate*> &map_updates)
{
  /* Sequentially iterate and update the map */
  for (int update_idx = 0; update_idx < map_updates.size(); update_idx++) {
    BattleGridMapUpdate *current_update = dynamic_cast<BattleGridMapUpdate *>(map_updates[update_idx]);

    switch (current_update->UpdateType()) {
      case 0:
        /*
         * PUT OPERATION
         *
         * A valid put operation is one in which the given agent isn't
         * already in some other spot
         */

        /* We will first move the agent if he already exists in another spot */
        if (isAgentInMap(current_update->agent) == true) {
          /* Remove the agent from his old spot */
          RemoveAgentFromRecords(current_update->agent);
        }

        /* Add the agent to the new spot */
        AddAgentToRecords(current_update->agent, tag);
        break;
      case 1:
        /*
         * DEL OPERATION
         *
         * A valid delete operation is one in which the agent is at the specified
         * position; in other words, delete only if update agent is at the
         * position, otherwise ignore silently
         */

        /* Ensure the relevant agent is in the grid */
        if (isAgentInMap(current_update->agent) == false) {
          break;
        }

        /* Ensure that this agent is in this position */
        /* This function could return a nullptr if the agent is not in the 
         * scene, but we've already checked for it, so no need to catch corner
         * case.
         */
        if (getAgentPosition(current_update->agent)->Compare(tag) == false) {
          break;
        }

        /* Deregister the agent from the records maintained by this map */
        /* Agent will be deallocated by the function call */
        RemoveAgentFromRecords(current_update->agent);
        break;

      default:
        Logger::Report ("Unidentified Update Provided.", Logger::WARN);
        break;
    }
  }
  return;
}



void BattleGridWorldMap::RegisterAgent(AbstractAgent *agent, AgentMethod method) {
      uint32_t x;
      uint32_t y;

      if (method == AgentMethod::RANDOM) {
        /* Random registering of the agent */
        std::vector<uint32_t> rand_int;
        RandUtils::GetEngine()->UniformRandomIntegers(0, width, 1, rand_int);
        x = rand_int.back();
        rand_int.pop_back();

        RandUtils::GetEngine()->UniformRandomIntegers(0, height, 1, rand_int);
        y = rand_int.back();
        rand_int.pop_back();
      }

      /* 
       * Create A New GridWorldPosition object and register it with the 
       * memory manager
       */

      /* FIXME: Find a way to keep track of this allocation */
      BattleGridPosition *new_position = new BattleGridPosition(x, y);
      
      AddAgentToRecords(agent, new_position);

      return;
}

AbstractPosition *BattleGridWorldMap::getAgentMapInfo(AbstractAgent *agent)
{
  /* Cast it into an agent of GridWorld */
  // GridAgent *grid_ag = dynamic_cast<GridAgent *> (agent);

  //return agent_to_pos[grid_ag];
}

