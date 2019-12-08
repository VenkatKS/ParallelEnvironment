# Multi-agent Parallel Environment

This folder contains the code for the meta-environment. The specific environments implemented should live as separate folders within this directory. The `core/` directory contains the files for the abstract classes parallelizing this framework.

According to the spec for creating new environments for the Gym, this has to be a Pip package by itself.

## Cython
In order to create the cython compiled package, run `python setup.py build_ext --inplace`
