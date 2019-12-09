#ifndef _ABSTRACT_ENV_H
#define _ABSTRACT_ENV_H

#include "abstract_map.h"
#include "recorder.h"
#include "common.h"

using ActionType = uint32_t;

class AbstractEnv {
  public:
    AbstractEnv (EnvBackend backend) : _current_backend(backend) {}

    virtual AbstractMap *getCurrentMap() = 0;
    virtual std::vector<AbstractAgent *> getAgents() = 0;
    virtual uint64_t getAgentRewards(AbstractAgent *agent) = 0;
    virtual bool isTerminal() = 0;

    virtual int getNumberOfAgents() { return this->getAgents().size(); }
    void dump_data(const std::vector<std::string>& header,
                   const std::string& filename, char mode);

    // Returns the rewards received by the agents when invoked.
    std::vector<uint64_t> step(std::vector<ActionType>& actions);

    // Cache list of agents so that we don't have to keep recreating
    // the agent-ID map
    std::vector<AbstractAgent*>& fetchAgents() {
        if (_agents.size() == 0) {
            _agents = this->getAgents();
            for (auto& _agent : _agents) {
                _id_to_agent[_agent->id()] = _agent;
            }
        }
        return _agents;
    }

  private:
    std::vector<uint64_t> seq_step(std::vector<ActionType>& actions);
    std::vector<uint64_t> omp_step(std::vector<ActionType>& actions);
    std::vector<uint64_t> mpi_step(std::vector<ActionType>& actions);

    std::vector<AbstractAgent*> _agents;
    std::unordered_map<int, AbstractAgent*> _id_to_agent;
    std::vector<int> _task_lengths;
    std::vector<int> _displacements;

    EnvBackend _current_backend;
    Recorder _run_recorder;
};
  
#endif
