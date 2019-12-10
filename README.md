# Parallel Environment Framework

The code requires MPIC++ to compile the MPI components, and OpenMP as well.

## C++

- In order to compile the exploration game, run `make`
The default name for the binary is `simple_exploration_env` and can be found in the `bin/` directory.

- In order to compile the battle game, run `make battle`.
The default name for the binary is `complex_battle_env` and can be found in the `bin/` directory.

The binary has a number of options which allow controlling the mode of execution:
- `-a <number_of_agents>` specifies the number of agents to simulate
- `-s <number_of_steps>` specifies the number of steps for which to run the simulation
- `-e <print_every>` specifies the interval after which a step status is displayed
- `-x <prefix-string>` if the dump file requries a prefix
- `-f <filename>` if you wish to override the default file name
- **one of** `-p`/`-m`: `-p` runs the program with OpenMP, `-m` runs it with OpenMP+MPI
NOTE: The OpenMPI+OpenMPI version still has to be run with `mpirun`. For instance,
`mpirun -np 4 -npernode 16 ./bin/run -a10000 -s100 -m -x"special"` would spawn
the program across 4 nodes with 16 threads.

_Not_ specifying either of `-p/m` utilizes the sequential version by default.
- `-d`: Disable dump file

## Python

Executing the `simulate_env.py` is similar to the CPP version. Please execute
`python simulate_env.py --help` to see the available options.
