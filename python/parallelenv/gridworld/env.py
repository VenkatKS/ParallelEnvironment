#!/usr/bin/env python3
import gym

from config import Log
from core.abstract_env import AbstractEnv
from gridworld.map import GridMap
from gridworld.agent import Agent

class RandomRewardGridEnv(AbstractEnv):

    def __init__(self, width=10, height=10, num_agents=2):
        super(RandomRewardGridEnv, self).__init__()
        self.map = GridMap(width=10, height=10)
        self.agents = list()
        for i in range(num_agents):
            self.agents.append(Agent(active_map=self.map))
            self.map.registerAgent(self.agents[-1])
        Log.warning("New env created with %d agents" % (len(self.agents)))

    def getCurrentMap(self):
        return self.map

    def getAgents(self):
        return self.agents

    def getAgentReward(self, agent):
        agent_pos = self.map.getAgentMapInfo(agent)
        return (agent_pos.x ** 2 + agent_pos.y ** 2)

    def isTerminal(self):
        return False
