from gridworld.env import RandomRewardGridEnv
from gridworld.agent import Agent

x = RandomRewardGridEnv()
x.step([Agent.AgentActions.FORWARD, Agent.AgentActions.TURN_UP])
