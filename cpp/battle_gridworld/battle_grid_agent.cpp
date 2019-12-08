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

  std::vector<uint32_t> action_vector;
  action_vector.push_back(action);
  return std::unordered_map<AbstractAgent *, std::vector<uint32_t>>{{this, action_vector}};
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




