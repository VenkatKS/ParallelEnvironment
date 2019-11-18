class AbstractAgent():
    # The abstract class for the Agent. 
    # The goal is to provide a framework for the agent's functionality within
    # the scope of a abstract environment.

    def __init__(self):
        pass
    
    @abstractmethod
    def getPossibleActions(self):
        # This method is to provide the agent with the ability to let the
        # upstream RL model be able to query the agent for information
        # regarding the actions that it can allow the model to instruct it
        # to perform.
        pass

    @abstractmethod
    def doAction(self, action):
        # This method is to provide the agent with the ability to convert
        # the actions generated by the model (i.e. the agent wise action)
        # into a format that is understandable by the middleware layer
        # that lies between the agent and the environment, or by the
        # environment itself.
        pass

    @abstractmethod
    def doActionAgentCollate(self, action_sequence):
        # This method allows the agent to view all of the actions it has to
        # take due to the environment and the actions of the other agents,
        # and generate a series of map updates that the map can understand.



