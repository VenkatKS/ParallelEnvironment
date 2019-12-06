.DEFAULT_GOAL := all

LOGGER_SRC_LIST = infra/logger.cpp 

LOGGER_OUT_PATH = bin/logger.o

UTILS_SRC_LIST = infra/utils.cpp

UTILS_OUT_PATH = bin/utils.o

SIMPLE_SRC_LIST = gridworld/main.cpp gridworld/gridmap.cpp

SIMPLE_DEPS = $(LOGGER_OUT_PATH) $(UTILS_OUT_PATH)

clean:
	@echo Running Clean
	rm -rf ./bin
	mkdir ./bin

logger:
	@echo Building Logger
	g++ --std=c++11 -Iinfra/include -c $(LOGGER_SRC_LIST) -o $(LOGGER_OUT_PATH)
utils:
	@echo Building Utility Functions
	g++ --std=c++11 -Iinfra/include -c $(UTILS_SRC_LIST) -o $(UTILS_OUT_PATH)

simple_gridworld: logger utils
	@echo Building Simple Gridworld Example
	g++ --std=c++11 -Icore/include -Iinfra/include -Igridworld/include \
	  $(SIMPLE_DEPS) $(SIMPLE_SRC_LIST)\
	  -o bin/run.o\

all: simple_gridworld


