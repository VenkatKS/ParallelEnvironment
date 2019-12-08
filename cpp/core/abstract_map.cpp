#include "abstract_map.h"
#include "abstract_grid_position.h"

#include <algorithm>
#include <omp.h>


bool AbstractMap::isAgentInMap(AbstractAgent *agent) {
  return (agent_to_pos.count(agent) > 0);
}

bool AbstractMap::doesPositionHaveAgents(AbstractPosition *position) {
  return (pos_to_agents.count(position) > 0);
}


AbstractPosition *AbstractMap::getAgentPosition(AbstractAgent *agent) {
  if (isAgentInMap(agent) == false) {
    return nullptr;
  }

  return agent_to_pos[agent];
}

bool AbstractMap::isAgentInPos(AbstractAgent *agent, AbstractPosition *position){
  return isAgentInMap(agent) && doesPositionHaveAgents(position) && \
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

void AbstractMap::doMapUpdates(std::unordered_map<AbstractPosition *, std::vector<AbstractUpdate *>> list_of_updates) {
    // FIXME: This is the sequential implementation of dispatch
    // if (_current_backend == EnvBackend::OMP) {
    //     this->doOmpMapUpdates(list_of_updates);
    //     return;
    // }

    // Else, do sequential implementation
    for (auto& kv_pair : list_of_updates) {
        this->doTaggedMapUpdates(kv_pair.first, kv_pair.second);
    }
}

void AbstractMap::doOmpMapUpdates(std::unordered_map<AbstractPosition*, std::vector<AbstractUpdate*>> list_of_updates) {
    auto* data = new std::vector<std::pair<AbstractPosition*, std::vector<AbstractUpdate*>*>>();
    for (auto& kv_pair : list_of_updates) {
        data->push_back(std::make_pair(kv_pair.first, &kv_pair.second));
    }
    #pragma omp parallel shared(data)
    for (int i = 0; i < data->size(); ++i) {
        this->doTaggedMapUpdates(data->at(i).first, *(data->at(i).second));
    }
    delete data;
}

/* FIXME: Use a tournament style algorithm to speed this up. Pending */
AbstractAgent *AbstractMap::GetNearestNeighbor(AbstractAgent *agent) {
  /* Do a linear scan thru the entire agent list to see the distances */
  std::unordered_map<AbstractAgent *, AbstractPosition *>::iterator agent_it;

  AbstractPosition *my_position = agent_to_pos[agent];

  uint32_t current_distance = GetMaxPossibleDistance();
  AbstractAgent *applicable_agent = nullptr;

  for (agent_it = agent_to_pos.begin(); agent_it != agent_to_pos.end(); \
      agent_it++) {
    /* Get the position of this agent */
    AbstractPosition *next_position = agent_it->second;

    /* Get the distance */
    AbstractDistance *this_distance = my_position->GetDistanceFrom\
                                      (next_position);
    if (this_distance->GetAbsolute() < current_distance) {
      current_distance = this_distance->GetAbsolute();
      applicable_agent = agent_it->first;
    }
    delete this_distance;
  }

  return applicable_agent;
}
