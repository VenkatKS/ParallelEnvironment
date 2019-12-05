#ifndef _ABSTRACT_UPDATES_H
#define _ABSTRACT_UPDATES_H

#include "abstract_agent.h"

class AbstractUpdate {
  public:

  AbstractAgent *agent;

  /* Provides an unique identifier to quickly see what kind of update this is */
  virtual uint32_t UpdateType() = 0;
};

#endif
