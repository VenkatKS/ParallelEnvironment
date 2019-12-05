.DEFAULT_GOAL := all

infra.o:
	g++ --std=c++11 -Iinfra/include -c infra/*.cpp -o bin/infra.o

simple_gridworld: infra.o
	g++ --std=c++11 -Icore/include -Iinfra/include -Igridworld/include \
	  bin/infra.o\
	  gridworld/main.cpp \
	  gridworld/gridmap.cpp\
	  -o bin/run.o\

all: infra.o simple_gridworld


