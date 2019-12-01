from enum import Enum
from collections import defaultdict

from core.abstract_agent import AbstractAgent
from config import Log

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
        self.__action_space = [s for s in self.AgentActions]

    def __init__(self, active_map, default_orientation = None, default_energy = 100):
        super(Agent, self).__init__()
        if default_orientation is None:
            default_orientation = Agent.Orientations.UP
        self.__SetupActionSpace()
        self.orientation = default_orientation
        self.energy = default_energy

        self.active_map = active_map

    def __repr__(self):
        return ("Agent{%s,%s,energy=%d}"
                "" % (hex(id(self)), self.orientation, self.energy))

    def getPossibleActions(self):
        return self.__action_space
    
    def doAction(self, action_int):
        # The input to this function is the output of the model. In that,
        # it is a single integer that specifies the action that the agent
        # has to take to ensure that it is able to make a proper move.
        action = Agent.AgentActions(action_int)
        if not action in self.__action_space:
            raise AssertionError (  "Agent has been provided an invalid" \
                                    " action space action.")
        
        # We need not do any transformation here, as the agent's actions
        # are limited to just moving around, so there is no reason to 
        # try to squash the actions here.
        return {self: [action]}

    def doActionAgentCollate(self, action_sequence):
        # Given an action space to perform, need to convert it into the
        # proper representation that the map can understand. In this case,
        # there are PUT and DEL actions.

        # Retrieve the current position of the agent within the active map
        current_pos = self.active_map.getAgentMapInfo(self)

        map_actions = defaultdict(list)
        for action in action_sequence:
            if (action == Agent.AgentActions.NO_MOVE):
                # The agent has decided to make no map-oriented moves
                pass
            elif (action == Agent.AgentActions.TURN_UP):
                # The agent is modifying an internal state and has no map updates
                # that it needs to report back to the map
                self.orientation = Agent.Orientations.UP
            elif (action == Agent.AgentActions.TURN_DOWN):
                # The agent is modifying an internal state and has no map updates
                # that it needs to report back to the map
                self.orientation = Agent.Orientations.DOWN
            elif (action == Agent.AgentActions.TURN_LEFT):
                # The agent is modifying an internal state and has no map updates
                # that it needs to report back to the map
                self.orientation = Agent.Orientations.LEFT
            elif (action == Agent.AgentActions.TURN_RIGHT):
                # The agent is modifying an internal state and has no map updates
                # that it needs to report back to the map
                self.orientation = Agent.Orientations.RIGHT
            elif (action == Agent.AgentActions.FORWARD):
                # Add the movement based on the current orientation of the
                # agent.
                new_x, new_y = current_pos.x, current_pos.y
                if (self.orientation == Agent.Orientations.UP):
                    new_y -= 1
                elif (self.orientation == Agent.Orientations.DOWN):
                    new_y += 1
                elif (self.orientation == Agent.Orientations.LEFT):
                    new_x -= 1
                elif (self.orientation == Agent.Orientations.RIGHT):
                    new_x += 1
                else:
                    raise AssertionError("Invalid Orientation")

                # If the new position is valid, move
                new_pos = self.active_map.GridPosition(new_x, new_y)
                if self.active_map.isValidPosition(new_pos):
                    map_actions[new_pos].append(self.active_map.PutMapUpdate(self))
                    # Delete the agent from the current location
                    map_actions[current_pos].append(self.active_map.DelMapUpdate(self))
            else:
                raise AssertionError("An invalid action has been specified")
        return map_actions
