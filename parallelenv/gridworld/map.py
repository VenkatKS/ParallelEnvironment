#!/usr/bin/env python3
import random

from config import Log
from core.abstract_map import AbstractMap
from collections import namedtuple

class GridMap(AbstractMap):
    """A 2D grid-based map environment."""

    GridPosition = namedtuple("GridPosition", "x y")
    PutMapUpdate = namedtuple("PutMapUpdate", "agent")
    DelMapUpdate = namedtuple("DelMapUpdate", "agent")

    # create new Put update : PutMapUpdate(agent=agent)

    def __init__(self, width, height):
        super(GridMap, self).__init__()
        self.width = width
        self.height = height

        self._agent_to_pos = dict()
        self._pos_to_agent = dict()

        self.__valid_updates__ = [GridMap.PutMapUpdate, 
                                  GridMap.DelMapUpdate]

    def doTaggedMapUpdates(self, grid_pos, mapUpdatesList):
        if (grid_pos.x < 0 or grid_pos.x >= self.width
                or grid_pos.y < 0 or grid_pos.y >= self.height):
            Log.warn("Skipping updates for invalid grid position %s" % (grid_pos))
            return
        self.__doSeqTaggedMapUpdates__(grid_pos, mapUpdatesList)

    def __doSeqTaggedMapUpdates__(self, tag, mapUpdatesList):
        if not isinstance(tag, GridMap.GridPosition):
            raise AssertionError("Expected tag to be an int "
                                 "(please refer to GridMap for definition)")
        if len([x for x in mapUpdatesList if type(x) not in self.__valid_updates__]) != 0:
            raise AssertionError("Found invalid update operation in {}"
                                 "".format(mapUpdatesList))

        # Separate out delete and put operations - we give precedence to delete
        # operations over put operations

        # A valid delete operation is one in which the agent is at the specified
        # position; in other words, delete only if update agent is at the
        # position, otherwise ignore silently
        del_updates = filter(lambda x: isinstance(x, GridMap.DelMapUpdate)
                                       and x.agent in self._agent_to_pos
                                       and self._agent_to_pos[x.agent] == tag,
                             mapUpdatesList)
        for del_update in del_updates:
            Log.debug("Tag: %s, executing DelMapUpdate %s" 
                      % (tag, del_update))
            agent_pos = self._agent_to_pos[del_update.agent]
            del self._agent_to_pos[del_update.agent]
            del self._pos_to_agent[agent_pos]

        # If this position is free and we have put operations, perform the first
        # one - all the rest will fail
        if tag not in self._pos_to_agent:
            # A valid put operation is one in which the given agent isn't
            # already in some other spot
            valid_puts = filter(lambda x: isinstance(x, GridMap.PutMapUpdate)
                                          and x.agent not in self._agent_to_pos,
                                mapUpdatesList)
            try:
                put_update = next(valid_puts)
                Log.debug("Tag: %s, executing PutMapUpdate %s" % (tag, put_update))
                if put_update.agent in self._agent_to_pos:
                    del self._pos_to_agent[self._agent_to_pos[put_update.agent]]
                self._pos_to_agent[tag] = put_update.agent
                self._agent_to_pos[put_update.agent] = tag
            except StopIteration:
                pass # Didn't have any valid put operations

    def getAgentMapInfo(self, agent):
        return self._agent_to_pos[agent]

    def getObservation(self):
        Log.warn("getObservation not implemented for GridMap!")
        return self

    def registerAgent(self, agent, method='random', **kwargs):
        # Registering randomly
        rand_x, rand_y = random.randint(0, self.width-1), random.randint(0, self.height-1)
        pos = GridMap.GridPosition(x=rand_x, y=rand_y)
        self._agent_to_pos[agent] = pos
        self._pos_to_agent[pos] = agent
        Log.debug("Registered new agent %s with position %s" % (hex(id(agent)), str(pos)))
