#ifndef _ABSTRACT_AGENT_H
#define _ABSTRACT_AGENT_H

#include "abstract_action.h"
#include "abstract_grid_position.h"

#include <string>
#include <unordered_map>
#include <vector>

/* Forward declare */
class AbstractUpdate;
class AbstractPosition;

class AbstractAgent {
  protected:

    /* Multiple views to avoid processing */
    std::unordered_map<std::string, uint32_t> registered_actions;
    std::vector<std::pair<std::string, uint32_t> > paired_actions;
    
    /*
     * Allow for the user agent to register the series of actions they want
     * to actuate. Likely comes from policy distribution specified by the user.
     *
     */
    void RegisterAction (std::string action_name, uint32_t enumerated_action);

  public:
    /*
     * This method is to provide the agent with the ability to let the
     * upstream RL model be able to query the agent for information
     * regarding the actions that it can allow the model to instruct it
     * to perform.
     */
    virtual ~AbstractAgent() = default;

    virtual uint32_t GetPossibleActions() = 0;
    // Returns a mapping between the agent to apply the action update to
    virtual std::unordered_map<AbstractAgent*, std::vector<uint32_t>> doAction(uint32_t action_id) = 0;

    virtual std::unordered_map<AbstractPosition *, AbstractUpdate *> doActionAgentCollate(std::vector<uint32_t> agent_actions) = 0;
};

#endif
