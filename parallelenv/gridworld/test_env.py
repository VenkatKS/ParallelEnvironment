from gridworld.env import RandomRewardGridEnv
from gridworld.agent import Agent

x = RandomRewardGridEnv()
print (x.step([Agent.AgentActions.TURN_UP, Agent.AgentActions.TURN_UP]))
