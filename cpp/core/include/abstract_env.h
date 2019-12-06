#ifndef _ABSTRACT_ENV_H
#define _ABSTRACT_ENV_H

#include "abstract_map.h"

class AbstractEnv {
  public:
    virtual AbstractMap *getCurrentMap() = 0;
    virtual std::vector<AbstractAgent *> getAgents() = 0;
    virtual uint64_t getAgentRewards(AbstractAgent *agent) = 0;
    virtual bool isTerminal() = 0;
};
  
#endif
