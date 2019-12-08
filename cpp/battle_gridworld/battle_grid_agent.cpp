#include "battle_grid_agent.h"
#include "battle_grid_map_updates.h"


BattleGridAgent::BattleGridAgent( BattleGridWorldMap *active_map, BattleGridAgentOrientation orientation, uint32_t default_energy, uint64_t id) : AbstractAgent (id)
{
  current_map = active_map;
  current_orientation = orientation;
  current_energy = default_energy;

  return;
}

BattleGridAgent::~BattleGridAgent() {
  return;
}

std::unordered_map<AbstractAgent *, std::vector<uint32_t>> BattleGridAgent::doAction(uint32_t action) {
  if (action >= BattleGridAgentActions::COUNT){ 
    Logger::Report ("Invalid action provided. No action will be taken.", Logger::LERR);
    throw 0;
  }
  
  BattleGridAgentActions chosen_action = static_cast<BattleGridAgentActions>(action);

  std::unordered_map<AbstractAgent *, std::vector<uint32_t>> packaged_actions;

  switch (action) {
    case BattleGridAgentActions::NO_MOVE:
    case BattleGridAgentActions::TURN_UP:
    case BattleGridAgentActions::TURN_DOWN:
    case BattleGridAgentActions::TURN_LEFT:
    case BattleGridAgentActions::TURN_RIGHT:
    case BattleGridAgentActions::FORWARD:
      {
        /* Only affects this agent, no need to perform a grid scan */
        std::vector<uint32_t> my_actions;
        my_actions.push_back(action);
        packaged_actions[this] = my_actions;
        return packaged_actions;
      }
    case BattleGridAgentActions::PUSH_NEAREST:
      /* Teleport to the nearest person and shove them */
      /* Once shoved, they move forward, and we teleport back and 
       * also move forward
       */
      /* Perform a scan */
      /* Move the other agent */
      {
        AbstractAgent *next_agent = current_map->GetNearestNeighbor(this);
        std::vector<uint32_t> other_actions;
        other_actions.push_back(BattleGridAgentActions::FORWARD);
        packaged_actions[next_agent] = other_actions;

        std::vector<uint32_t> my_actions;
        my_actions.push_back(BattleGridAgentActions::FORWARD);
        packaged_actions[this] = my_actions;
        return packaged_actions;
      }
    default:
      Logger::Report("Unknown action!!", Logger::LERR);
      exit(-1);
  }

  return packaged_actions;
}

std::unordered_map<AbstractPosition *, AbstractUpdate *> \
    BattleGridAgent::doActionAgentCollate(std::vector<uint32_t> agent_actions) {

  BattleGridPosition *pos = dynamic_cast<BattleGridPosition *>\
                      (current_map->getAgentMapInfo(this));

  std::unordered_map<AbstractPosition *, AbstractUpdate *> updates; 
  for (uint32_t update_action : agent_actions) {
    BattleGridAgentActions this_action = static_cast<BattleGridAgentActions> \
                                         (update_action);

    if (this_action == BattleGridAgentActions::NO_MOVE) {
      /* No local or map updates necessary. */
    } else if (this_action == BattleGridAgentActions::TURN_UP) {
      /* The agent is modifying an internal state and has no map updates */
      current_orientation = BattleGridAgentOrientation::UP;
    } else if (this_action == BattleGridAgentActions::TURN_DOWN /*for what?*/) {
      /* The agent is modifying an internal state and has no map updates */
      current_orientation = BattleGridAgentOrientation::DOWN;
    } else if (this_action == BattleGridAgentActions::TURN_LEFT) {
      /* The agent is modifying an internal state and has no map updates */
      current_orientation = BattleGridAgentOrientation::LEFT;
    } else if (this_action == BattleGridAgentActions::TURN_RIGHT) {
      /* The agent is modifying an internal state and has no map updates */
      current_orientation = BattleGridAgentOrientation::RIGHT;
    } else if (this_action == BattleGridAgentActions::FORWARD) {
      uint32_t this_x = pos->x;
      uint32_t this_y = pos->y;
      if (current_orientation == BattleGridAgentOrientation::UP)
        this_y -= 1;
      else if (current_orientation == BattleGridAgentOrientation::DOWN)
        this_y += 1;
      else if (current_orientation == BattleGridAgentOrientation::LEFT)
        this_x -= 1;
      else if (current_orientation == BattleGridAgentOrientation::RIGHT)
        this_y += 1;
      else
        throw "Error dir.";

      /* requires map updates here */
      BattleGridPosition *new_pos = new BattleGridPosition(this_x, this_y);
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

uint32_t BattleGridAgent::GetPossibleActions() {
  return BattleGridAgentActions::COUNT;
}




