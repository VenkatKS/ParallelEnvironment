#!/usr/bin/env python3
import gym
from collections import defaultdict
from abc import ABC, abstractmethod

from config import Log

class AbstractEnv(ABC, gym.Env):
    """Base class for defining the reward structure over different maps, and
    for managing agents interacting in the environment.

    This class serves as the interface through which client models interact with
    the environment, and therefore also inherits from gym.Env. This environment
    is responsible for orchestrating the interaction with internal-facing Agent
    and Map classes.

    All subclasses are required to implement methods marked as abstract.
    """

    @abstractmethod
    def getCurrentMap(self):
        """Returns the underlying subclass of AbstractMap initialized by the implementation.

        Returns
        -------
        current_map : AbstractMap, required
            A reference to the current instance of AbstractMap maintained by the 
            subclass
        """
        return

    @abstractmethod
    def getAgents(self):
        """Returns agents maintained by underlying implementation.

        Returns
        -------
        agent_list : list of AbstractAgent, required
            Current set of agents known to the environment
        """

    @abstractmethod
    def getAgentReward(self, agent):
        """Returns the reward for an agent on the basis of the post-step (new) map,
        and the pre-step (old) map.

        It is assumed that executing this function is concurrency-safe.

        Parameters
        ----------
        agent: object, required
            The agent for which the reward needs to be computed

        Returns
        -------
        reward: float32, required
            The reward awarded to the agent
        """

    @abstractmethod
    def isTerminal(self):
        """Returns whether the current game is done, on the basis of the map and reward structure."""

    def __init__(self):
        super(AbstractEnv, self).__init__()

    def step(self, action):
        Log.debug("=================== New Step ===================")
        return self.__doSequentialStep__(action)

    def __doSequentialStep__(self, actions):
        # Invoke agent actions
        # Also, reduce agent-actionUpdates
        agent_list = self.getAgents()
        agent_action_updates = defaultdict(list)
        for agent, action in zip(agent_list, actions):
            updates = agent.doAction(action)
            for agent, action_list in updates.items():
                agent_action_updates[agent].extend(action_list)
        Log.debug("Agent->action_updates are %s" % (agent_action_updates))

        # Invoke agent action updates
        # Also, reduce tag-mapUpdates
        tag_map_updates = defaultdict(list)
        for agent, action_updates in agent_action_updates.items():
            map_update = agent.doActionAgentCollate(action_updates)
            Log.debug("Agent %s update %s" % (hex(id(agent)), map_update))
            for tag, update_list in map_update.items():
                tag_map_updates[tag].extend(update_list)
        del agent_action_updates
        Log.debug("Tag->map_updates are %s" % (tag_map_updates))

        # Invoke map updates
        current_map = self.getCurrentMap()
        current_map.doMapUpdates(tag_map_updates)
        del tag_map_updates

        # Get reward for all the agents
        agent_rewards = []
        for agent in agent_list:
            agent_rewards.append(self.getAgentReward(agent))
        Log.debug("Agent rewards are %s"
                   % ([(hex(id(agent)), agent_rewards[i]) for i, agent in enumerate(agent_list)]))

        return current_map.getObservation(), agent_rewards, self.isTerminal(), None

    def reset(self):
        raise NotImplementedError("Haven't implemented raise yet")
