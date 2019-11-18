from enum import Enum
from abstract_agent import AbstractAgent

class Agent(AbstractAgent):
    class AgentActions(Enum):
        # Set angle to 90 degrees
        TURN_UP = 0
        # Set angle to 270 degrees
        TURN_DOWN = 1
        # Set angle to 180 degrees
        TURN_LEFT = 2
        # Set angle to 0 degrees
        TURN_RIGHT = 3

        # Make a step in the direction
        # the agent is currently facing
        # in.
        FORWARD = 4
        NO_MOVE = 5

    class Orientations(Enum):
        UP = 0
        DOWN = 1
        LEFT = 2
        RIGHT = 3

    def __SetupActionSpace(self):
        self.__action_space = [s for s in AgentActions]

    def __init__(self, active_map, default_orientation = Orientations.UP, \
            default_energy = 100):

        super(Agent, self).__init__()
        self.__SetupActionSpace()
        self.orientation = default_orientation
        self.energy = default_energy

        self.active_map = active_map

    @override
    def getPossibleActions(self):
        return self.__action_space
    
    @override
    self doAction(self, action):
        # The input to this function is the output of the model. In that,
        # it is a single integer that specifies the action that the agent
        # has to take to ensure that it is able to make a proper move.
        if not isinstance(action, int):
            raise AssertionError(   "Agent input expects a single int action" \
                                    " that the model has requested this" \
                                    "agent perform.")

        if not action in self.__action_space:
            raise AssertionError (  "Agent has been provided an invalid" \
                                    " action space action.")
        
        # We need not do any transformation here, as the agent's actions
        # are limited to just moving around, so there is no reason to 
        # try to squash the actions here.
        return {self: [action]}

    @override
    def doActionAgentCollate(self, action_sequence):
        # Given an action space to perform, need to convert it into the
        # proper representation that the map can understand. In this case,
        # there are PUT and DEL actions.

        # Retrieve the current position of the agent within the active map
        current_pos = self.active_map.getAgentMapInfo(self)["position"]

        map_actions = {}
        for action in action_sequence:
            if (action == AgentActions.NO_MOVE):
                # The agent has decided to make no map-oriented moves
                pass
            elif (action == AgentActions.TURN_UP):
                # The agent is modifying an internal state and has no map updates
                # that it needs to report back to the map
                self.orientation = Orientations.UP
            elif (action == AgentActions.TURN_DOWN):
                # The agent is modifying an internal state and has no map updates
                # that it needs to report back to the map
                self.orientation = Orientations.DOWN
            elif (action == AgentActions.TURN_LEFT):
                # The agent is modifying an internal state and has no map updates
                # that it needs to report back to the map
                self.orientation = Orientations.LEFT
            elif (action == AgentActions.TURN_RIGHT):
                # The agent is modifying an internal state and has no map updates
                # that it needs to report back to the map
                self.orientation = Orientations.RIGHT
            elif (action == AgentActions.MOVE_FORWARD):
                # Delete the agent from the current location
                if not current_pos in map_actions:
                    map_actions[current_pos] = []

                map_actions[current_pos].append(active_map.DelMapUpdate(self))

                # Add the movement based on the current orientation of the
                # agent.
                if (self.orientation == Orientations.UP):
                    current_pos["y"] -= 1
                elif (self.orientation == Orientations.DOWN):
                    current_pos["y"] += 1
                elif (self.orientation == Orientations.LEFT):
                    current_pos["x"] -= 1
                elif (self.orientation == Orientations.RIGHT):
                    current_pos["x"] += 1
                else:
                    raise AssertionError("Invalid Orientation")

                if not current_pos in map_actions:
                    map_actions[current_pos] = []

                map_actions[current_pos].append(active_map.PutMapUpdate(self))

            else:
                raise AssertionError("An invalid action has been specified")
        return map_actions
                


