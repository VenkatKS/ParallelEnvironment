#!/usr/bin/env python3
from core.abstract_map import AbstractMap
from collections import namedtuple

class GridMap(AbstractMap):
    """A 2D grid-based map environment."""

    PutMapUpdate = namedtuple("PutMapUpdate", "agent")
    DelMapUpdate = namedtuple("DelMapUpdate", "agent")

    def __init__(self, width, height):
        self.width = width
        self.height = height

        self._agent_to_pos = dict()
        self._pos_to_agent = dict()

        self.__valid_updates__ = [GridMap.PutMapUpdate, 
                                  GridMap.DelMapUpdate]

    def doTaggedMapUpdates(self, tag, mapUpdatesList):
        __doSeqTaggedMapUpdates__(tag, mapUpdatesList)

    def __doSeqTaggedMapUpdates__(self, tag, mapUpdatesList):
        if not isinstance(tag, int):
            raise AssertionError("Expected tag to be an int "
                                 "(please refer to GridMap for definition)")
            if len([x for x in mapUpdatesList if type(x) not in self.__valid_updates__]) != 0:
                raise AssertionError("Found invalid update operation in {}"
                                     "".format(mapUpdatesList))

        # Separate out delete and put operations - we give precedence to delete
        # operations over put operations
        del_updates = filter(lambda x: isinstance(x, DelMapUpdate), mapUpdatesList)
        for del_update in del_updates:
            agent_pos = self._agent_to_pos[del_update.agent]
            del self._agent_to_pos[del_update.agent]
            del self._pos_to_agent[agent_pos]

        # If this position is free and we have put operations, perform the first
        # one - all the rest will fail
        if tag not in self._pos_to_agent:
            put_update = next(filter(lambda x: isinstance(x, PutMapUpdate)))
            if put_update.agent in self._agent_to_pos:
                del self._pos_to_agent[self._agent_to_pos[put_update.agent]]
            self._pos_to_agent[tag] = put_update.agent
            self._agent_to_pos[put_update.agent] = tag

    def getAgentMapInfo(self, agent):
        return self._agent_to_pos[agent]
