#include "gridagent.h"
#include "grid_map.h"
#include "logger.h"


GridAgent::GridAgent(GridWorldMap *active_map, GridAgentOrientation default_orientation,
                     uint32_t default_energy, uint64_t id) : AbstractAgent(id) {
  current_map = active_map;
  current_orientation = default_orientation;
  current_energy = default_energy;
}

GridAgent::~GridAgent() {
  return;
}

std::unordered_map<AbstractAgent*, std::vector<uint32_t>> GridAgent::doAction(uint32_t action) {
  /* Verify if the agent is proper */
  if (action >= GridAgentActions::COUNT) {
    throw "Invalid action provided.";
    Logger::Report("Invalid action provided.", Logger::FERR);
  }
    
  /* Convert the action into our enumeration */
  /* GridAgentAction action_index = static_cast<GridAgentAction>(action); */
  
  std::vector<uint32_t> action_vector;
  action_vector.push_back(action);

  return std::unordered_map<AbstractAgent*, std::vector<uint32_t>>{{this, action_vector}};
}

std::unordered_map<AbstractPosition *, AbstractUpdate *> GridAgent::doActionAgentCollate(std::vector<uint32_t> agent_actions) {
  GridPosition *pos = dynamic_cast<GridPosition *>\
                      (current_map->getAgentMapInfo(this));

  std::unordered_map<AbstractPosition *, AbstractUpdate *> updates; 

  for (uint32_t update_action : agent_actions) {
    GridAgentActions this_action = static_cast<GridAgentActions> (update_action);

    if (this_action == GridAgentActions::NO_MOVE) {
      /* No local or map updates necessary. */
    } else if (this_action == GridAgentActions::TURN_UP) {
      /* The agent is modifying an internal state and has no map updates */
      current_orientation = GridAgentOrientation::UP;
    } else if (this_action == GridAgentActions::TURN_DOWN /*for what?*/) {
      /* The agent is modifying an internal state and has no map updates */
      current_orientation = GridAgentOrientation::DOWN;
    } else if (this_action == GridAgentActions::TURN_LEFT) {
      /* The agent is modifying an internal state and has no map updates */
      current_orientation = GridAgentOrientation::LEFT;
    } else if (this_action == GridAgentActions::TURN_RIGHT) {
      /* The agent is modifying an internal state and has no map updates */
      current_orientation = GridAgentOrientation::RIGHT;
    } else if (this_action == GridAgentActions::FORWARD) {
      uint32_t this_x = pos->x;
      uint32_t this_y = pos->y;
      if (current_orientation == GridAgentOrientation::UP)
        this_y -= 1;
      else if (current_orientation == GridAgentOrientation::DOWN)
        this_y += 1;
      else if (current_orientation == GridAgentOrientation::LEFT)
        this_x -= 1;
      else if (current_orientation == GridAgentOrientation::RIGHT)
        this_y += 1;
      else
        throw "Error dir.";

      /* requires map updates here */
      GridPosition *new_pos = new GridPosition(this_x, this_y);
      if (current_map->isValidPosition(new_pos)) {
        /* The position can be moved into */
        updates[new_pos] = new PutMapUpdate();
        updates[new_pos]->agent = this;

        updates[pos] = new DelMapUpdate();
        updates[pos]->agent = this;
      }
      return updates;

    } else {
      throw "Illegal action per se see?";
      exit(-1); /* meh */
    }
  }

  return updates;
}


uint32_t GridAgent::GetPossibleActions()
{
  return GridAgentActions::COUNT;
}
