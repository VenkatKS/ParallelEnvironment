#ifndef _GRID_AGENT_H
#define _GRID_AGENT_H

#include "abstract_agent.h"
#include "abstract_grid_position.h"
#include "abstract_updates.h"

#include "grid_map.h"

enum GridAgentActions {
  NO_MOVE,
  TURN_UP,
  TURN_DOWN,
  TURN_LEFT,
  TURN_RIGHT,
  FORWARD,
  /* When adding new actions, add above this line */
  COUNT
};

enum GridAgentOrientation {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class GridAgent : public AbstractAgent {
  public:
    /* Provides the initial energies for the agents */
    GridAgent(GridWorldMap *active_map, GridAgentOrientation orientation, \
        uint32_t default_energy, uint64_t id);
    ~GridAgent();
    
  private:
    uint32_t max_allowed_actions = GridAgentActions::COUNT;

    GridAgentOrientation current_orientation;
    uint32_t current_energy;
    GridWorldMap *current_map; 

  public:
    virtual uint32_t GetPossibleActions();
    virtual std::unordered_map<AbstractAgent*, std::vector<uint32_t>> doAction(uint32_t action_id);
    virtual std::unordered_map<AbstractPosition *, AbstractUpdate *> doActionAgentCollate(std::vector<uint32_t> agent_actions);
};


#endif
