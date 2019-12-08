import random
import argparse
import numpy as np

from gridworld.env import RandomRewardGridEnv
from gridworld.agent import Agent

parser = argparse.ArgumentParser(description='Simulate grid environment')
parser.add_argument('--height', type=int, default=1000, required=False)
parser.add_argument('--width', type=int, default=1000, required=False)
parser.add_argument('--num_agents', type=int, default=int(1e5), required=False)
parser.add_argument('--num_steps', type=int, default=100, required=False)
parser.add_argument('--filename', type=str, required=False, default=None)
parser.add_argument('--filemode', type=str, default="w", choices=['w', 'a'], required=False)
parser.add_argument('--every', type=int, default=100)
parser.add_argument('--type', type=str, choices=['seq'], default='seq')
parser.add_argument('--datadir', type=str, default='data/')

args = parser.parse_args()

filename = args.filename
if filename is None:
    filename = ("{type}-a-{agents}k-s-{steps}k-g-{width}x{height}.csv"
                "".format(type=args.type, agents=args.num_agents//1000,
                          steps=args.num_steps//1000, width=args.width, height=args.height))
filename = args.datadir + filename
print ("Going to dump to file %s" % (filename))

print ("Creating environment")
x = RandomRewardGridEnv(width=args.width, height=args.height,
                        num_agents=args.num_agents)

print ("Starting simulation for %d steps with %d agents" % (args.num_steps, args.num_agents))
for i in range(args.num_steps):
    if i % args.every == 0:
        print ("On step %d" % (i))
    x.step(np.random.randint(low=0, high=6, size=args.num_agents))
x.dump_timing(filename, mode=args.filemode)
