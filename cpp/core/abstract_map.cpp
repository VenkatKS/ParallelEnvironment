#include "abstract_map.h"


bool AbstractMap::isAgentInMap(AbstractAgent *agent) {
  return (agent_to_pos.count(agent) > 0);
}

bool AbstractMap::isValidPosition(AbstractPosition *position) {
  return (pos_to_agents.count(position) > 0);
}


AbstractPosition *AbstractMap::getAgentPosition(AbstractAgent *agent) {
  if (isAgentInMap(agent) == false) {
    return nullptr;
  }

  return agent_to_pos[agent];
}

bool AbstractMap::isAgentInPos(AbstractAgent *agent, AbstractPosition *position){
  return isAgentInMap(agent) && isValidPosition(position) && \
    (std::count(pos_to_agents[position].begin(), pos_to_agents[position].end(),
                agent) > 0);
}

void AbstractMap::RemoveAgentFromRecords(AbstractAgent *agent) {
  if (isAgentInMap(agent) == false) {
    return;
  }

  AbstractPosition *loc = agent_to_pos[agent];

  /* Remove the agent from the agent->pos mapping */
  agent_to_pos.erase(agent);
  
  /* Remove the agent from the pos->agent mapping */
  pos_to_agents[loc].erase(std::remove(pos_to_agents[loc].begin(), \
        pos_to_agents[loc].end(), agent), pos_to_agents[loc].end());

  delete agent;
  return;
}


void AbstractMap::AddAgentToRecords(AbstractAgent *agent, AbstractPosition *pos) {
  /* Don't double add the agent to the map records */
  if (isAgentInMap(agent) == true)
    return;

  agent_to_pos[agent] = pos;
  pos_to_agents[pos].push_back(agent);
  return;
}

AbstractMap *AbstractMap::getObservation() {
  return this;
}

void AbstractMap::doMapUpdates(std::unordered_map<AbstractPosition *, AbstractUpdate *> list_of_updates) {
    return;
}
