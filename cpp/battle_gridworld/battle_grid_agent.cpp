#include "battle_grid_agent.h"


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
      /* Perform a scan */
      break;
  }

  return packaged_actions;
}

std::unordered_map<AbstractPosition *, AbstractUpdate *> \
    BattleGridAgent::doActionAgentCollate(std::vector<uint32_t> agent_actions) {
  std::unordered_map<AbstractPosition *, AbstractUpdate *> updates;
  /* FIXME: Implement these */
  return updates;
}

uint32_t BattleGridAgent::GetPossibleActions() {
  return BattleGridAgentActions::COUNT;
}




