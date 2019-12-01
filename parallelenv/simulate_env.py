import random
import argparse

from gridworld.env import RandomRewardGridEnv
from gridworld.agent import Agent

parser = argparse.ArgumentParser(description='Simulate grid environment')
parser.add_argument('--height', type=int, default=1000, required=False)
parser.add_argument('--width', type=int, default=1000, required=False)
parser.add_argument('--num_agents', type=int, default=int(1e5), required=False)
parser.add_argument('--num_steps', type=int, default=100, required=False)

args = parser.parse_args()

print ("Creating environment")
x = RandomRewardGridEnv(width=args.width, height=args.height,
                        num_agents=args.num_agents)

print ("Starting simulation for %d steps with %d agents" % (args.num_steps, args.num_agents))
for i in range(args.num_steps):
    if i % 100 == 0:
        print ("On step %d" % (i))
    x.step([random.randint(0, 5), random.randint(0, 5)])
x.dump_timing('test.csv')
