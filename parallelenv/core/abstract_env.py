#!/usr/bin/env python3
import gym
from abc import ABC, abstractmethod

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
        self.__doSequentialStep__(action)

    def __doSequentialStep__(self, actions):
        # Invoke agent actions
        # Also, reduce agent-actionUpdates
        agent_list = self.getAgents()
        agent_action_updates = dict()
        for agent, action in zip(agent_list, actions)
            updates = agent.doAction(action)
            for update in updates:
                agent_action_updates[update.agent] = update.action

        # Invoke agent action updates
        # Also, reduce tag-mapUpdates
        tag_map_updates = dict()
        for agent, action_updates in agent_action_updates.items():
            map_update = agent.doActionCollate(action_updates)
            for update in map_update:
                tag_map_updates[update.tag] = update.map_update
        del agent_action_updates

        # Invoke map updates
        current_map = self.getCurrentMap()
        for tag, map_update in tag_map_updates.items():
            current_map.doMapUpdates(tag, map_update)
        del tag_map_updates

        # Get reward for all the agents
        agent_rewards = []
        for idx, agent in enumerate(agent_list):
            agent_rewards[idx] = current_map.getAgentReward(agent)

        return current_map.getObservation(), agent_rewards, self.isTerminal(), _

    def reset(self):
        raise NotImplementedError("Haven't implemented raise yet")
