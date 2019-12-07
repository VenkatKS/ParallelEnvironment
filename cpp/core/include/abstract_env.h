#ifndef _ABSTRACT_ENV_H
#define _ABSTRACT_ENV_H

#include "abstract_map.h"
#include "recorder.h"

using ActionType = uint32_t;

class AbstractEnv {
  public:
    virtual AbstractMap *getCurrentMap() = 0;
    virtual std::vector<AbstractAgent *> getAgents() = 0;
    virtual uint64_t getAgentRewards(AbstractAgent *agent) = 0;
    virtual bool isTerminal() = 0;

    void dump_data(const std::vector<std::string>& header,
                   const std::string& filename, char mode);

    // Returns the rewards received by the agents when invoked.
    std::vector<uint64_t> step(const std::vector<ActionType>& actions);

  private:
    Recorder _run_recorder;
};
  
#endif
