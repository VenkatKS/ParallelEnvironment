#ifndef _ABSTRACT_ENV_H
#define _ABSTRACT_ENV_H

#include "abstract_map.h"

class AbstractEnv {
  private:
  protected:
  public:
    virtual AbstractMap getCurrentMap() = 0;
    virtual std::vector<AbstractAgent> getAgents() = 0;
    virtual uint64_t getAgentRewards() = 0;
    virtual bool isTerminal() = 0;
};
  
#endif
