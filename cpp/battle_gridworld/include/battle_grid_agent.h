#ifndef _BATTLE_GRID_AGENT_H
#define _BATTLE_GRID_AGENT_H

#include "abstract_agent.h"
#include "abstract_grid_position.h"
#include "abstract_updates.h"
#include "battle_grid_map.h"

enum BattleGridAgentActions {
  NO_MOVE,
  TURN_UP,
  TURN_DOWN,
  TURN_LEFT,
  TURN_RIGHT,
  FORWARD,
  PUSH_FORWARD,
  /* Add above this line */
  COUNT
};

enum BattleGridAgentOrientation {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class BattleGridAgent : public AbstractAgent {
  public:
    /* Provides the initial energies for the agents */
    BattleGridAgent(BattleGridWorldMap *active_map, BattleGridAgentOrientation orientation, \
        uint32_t default_energy, uint64_t id);
    ~BattleGridAgent();
    
  private:
    uint32_t max_allowed_actions = BattleGridAgentActions::COUNT;

    BattleGridAgentOrientation current_orientation;
    uint32_t current_energy;
    BattleGridWorldMap *current_map; 

  public:
    virtual uint32_t GetPossibleActions();
    virtual std::unordered_map<AbstractAgent*, std::vector<uint32_t>> doAction(uint32_t action_id);
    virtual std::unordered_map<AbstractPosition *, AbstractUpdate *> doActionAgentCollate(std::vector<uint32_t> agent_actions);
};




#endif
