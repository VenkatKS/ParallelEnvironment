/* The concrete instantiation of MAP */

#include "grid_map.h"
#include "grid_position.h"
#include "logger.h"
#include "grid_map_updates.h"

bool GridWorldMap::isValidPosition(GridPosition grid_pos) {
  /* Ensure the provided coordinates is within the board's height and width*/
  if (grid_pos.x < 0 || grid_pos.x >= width
          || grid_pos.y < 0 || grid_pos.y >= height) {
      return false;
  }

  return true;
}

void GridWorldMap::doTaggedMapUpdates(GridPosition active_position, \
    std::vector<AbstractUpdate*> map_updates) {

  /* Sanitize the input and see if there are any errors. */
  for (int update_idx = 0; update_idx < map_updates.size(); update_idx++) {
    Logger::Report("Invalid position for agent update.", Logger::LERR);
    Logger::DumpPipes(Logger::ALL);
    exit(-1);
  }

  doSeqTaggedMapUpdates(active_position, map_updates);
  return;
}

void GridWorldMap::doSeqTaggedMapUpdates(GridPosition tag,\
                                         std::vector<AbstractUpdate*> map_updates)
{
  /* Sequentially iterate and update the map */
  for (int update_idx = 0; update_idx < map_updates.size(); update_idx++) {
    GridMapUpdate *current_update = dynamic_cast<GridMapUpdate *>(map_updates[update_idx]);

    switch (current_update->UpdateType()) {
      case 0:
        /* PUT */
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
          continue;
        }

        break;
      default:
        Logger::Report ("Unidentified Update Provided.", Logger::WARN);
        break;
    }
  }

  return;
}




