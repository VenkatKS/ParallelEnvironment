#ifndef _ABSTRACT_AGENT_H
#define _ABSTRACT_AGENT_H

#include <string>
#include <unordered_map>
#include <vector>

class ActionAlreadyRegisteredException {
  public:
    ActionAlreadyRegisteredException() {
    }

    ~ActionAlreadyRegisteredException() {
    }
};

class AbstractAgent {
  protected:

    /* Multiple views to avoid processing */
    std::unordered_map<std::string, uint32_t> registered_actions;
    std::vector<std::pair<std::string, uint32_t> > paired_actions;
    
    /*
     * Allow for the user agent to register the series of actions they want
     * to actuate. Likely comes from policy distribution specified by the user.
     *
     * Throws:
     *          1. ActionAlreadyRegisteredException: The action was already registered.
     */
    void RegisterAction (std::string action_name, uint32_t enumerated_action) {
      std::unordered_map<std::string, uint32_t>::iterator it = \
          registered_actions.find(action_name); 

      /* If the specified action is already in the dictionary, don't allow */
      if(it != registered_actions.end()) {
        throw ActionAlreadyRegisteredException();
      }

      registered_actions[action_name] = enumerated_action;
      paired_actions.push_back(std::pair<std::string, uint32_t>(action_name,\
            enumerated_action));
      return;
    }

  public:
    /*
     * This method is to provide the agent with the ability to let the
     * upstream RL model be able to query the agent for information
     * regarding the actions that it can allow the model to instruct it
     * to perform.
     */
    virtual std::vector<std::pair<std::string, uint32_t> > GetPossibleActions() {
      return paired_actions;
    }
};

#endif
