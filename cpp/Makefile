.DEFAULT_GOAL := all

FRAMEWORK_SRC_LIST = core/abstract_agent.cpp core/abstract_map.cpp
FRAMEWORK_INC_LIST = -Icore/include
FRAMEWORK_FLAGS = -shared
FRAMEWORK_OUT_PATH = bin/framework.a

LOGGER_SRC_LIST = infra/logger.cpp 
LOGGER_INC_LIST = -Iinfra/include
LOGGER_OUT_PATH = bin/logger.o

UTILS_SRC_LIST = infra/utils.cpp
UTILS_INC_LIST = -Iinfra/include

UTILS_OUT_PATH = bin/utils.o

SIMPLE_SRC_LIST = gridworld/main.cpp gridworld/gridmap.cpp gridworld/gridenv.cpp
SIMPLE_INC_LIST = -Igridworld/include

SIMPLE_DEPS = $(LOGGER_OUT_PATH) $(UTILS_OUT_PATH) $(FRAMEWORK_OUT_PATH)

clean:
	@echo Running Clean
	rm -rf ./bin
	mkdir ./bin

logger:
	@echo Building Logger
	g++ --std=c++11 $(LOGGER_INC_LIST) -c $(LOGGER_SRC_LIST) -o $(LOGGER_OUT_PATH)
utils:
	@echo Building Utility Functions
	g++ --std=c++11 $(UTILS_INC_LIST)  -c $(UTILS_SRC_LIST) -o $(UTILS_OUT_PATH)
framework: logger utils
	@echo Building Framework
	g++ --std=c++11 $(FRAMEWORK_FLAGS) $(FRAMEWORK_INC_LIST) $(LOGGER_INC_LIST) $(UTILS_INC_LIST) $(FRAMEWORK_SRC_LIST) -o $(FRAMEWORK_OUT_PATH)
	@echo Done

simple_gridworld: logger utils framework
	@echo Building Simple Gridworld Example
	g++ --std=c++11 $(FRAMEWORK_INC_LIST) $(UTILS_INC_LIST) $(LOGGER_INC_LIST) $(SIMPLE_INC_LIST)\
	  $(SIMPLE_DEPS) $(SIMPLE_SRC_LIST)\
	  -o bin/run.o\

all: simple_gridworld


