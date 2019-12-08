#ifndef _BATTLE_MAP_UPDATES_H
#define _BATTLE_MAP_UPDATES_H

class BattleGridMapUpdate : public AbstractUpdate {
};

class PutMapUpdates : public BattleGridMapUpdate { 
  public:
    uint32_t UpdateType() {
      return 0;
    }    
};

class DelMapUpdate : public BattleGridMapUpdate {
  public:
    uint32_t UpdateType() {
      return 1;
    }
};

#endif
