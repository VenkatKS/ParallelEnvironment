#include "abstract_agent.h"


void AbstractAgent::RegisterAction (std::string action_name, uint32_t enumerated_action) {
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

std::vector<std::pair<std::string, uint32_t> > AbstractAgent::GetPossibleActions() {
  return paired_actions;
}
