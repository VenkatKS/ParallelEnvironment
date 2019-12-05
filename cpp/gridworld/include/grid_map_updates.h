#ifndef _GRID_MAP_UPDATES_H
#define _GRID_MAP_UPDATES_H

#include "abstract_updates.h"

class GridMapUpdate : public AbstractUpdate {
};

class PutMapUpdate : public GridMapUpdate { 
public:
  /* Provides an unique identifier to quickly see what kind of update this is */
  uint32_t UpdateType() {
    return 0;
  }

};

class DelMapUpdate : public GridMapUpdate {
public:

  /* Provides an unique identifier to quickly see what kind of update this is */
  uint32_t UpdateType() {
    return 1;
  }
};

#endif
