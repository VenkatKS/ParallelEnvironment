.DEFAULT_GOAL := all

# ==================== Framework Core Definitions ========================
FRAMEWORK_SRC_LIST = core/abstract_agent.cpp core/abstract_map.cpp core/abstract_env.cpp
FRAMEWORK_INC_LIST = -Icore/include
FRAMEWORK_FLAGS = -shared -fpic -fopenmp
FRAMEWORK_OUT_PATH = bin/framework.a
# =========================================================================

# ==================== Logger Infrastructure Definitions ==================
LOGGER_SRC_LIST = infra/logger.cpp 
LOGGER_INC_LIST = -Iinfra/include
LOGGER_OUT_PATH = bin/logger.o
# ===========================================================================

# ==================== Utility Infrastructure Definitions ==================
UTILS_SRC_LIST = infra/utils.cpp
UTILS_INC_LIST = -Iinfra/include
# ===========================================================================

# ==================== Recorder Infrastructure Definitions ==================
RECORDER_SRC_LIST = infra/recorder.cpp
RECORDER_INC_LIST = -Iinfra/include
RECORDER_OUT = bin/recorder.o

UTILS_OUT_PATH = bin/utils.o
# ===========================================================================

# ==================== Exploration Environment Definitions ==================
EXPLORATION_ENV_SRC_LIST = gridworld/main.cpp gridworld/gridmap.cpp gridworld/gridenv.cpp gridworld/gridagent.cpp
EXPLORATION_ENV_INC_LIST = -Igridworld/include

EXPLORATION_ENV_DEPS = $(LOGGER_OUT_PATH) $(RECORDER_OUT) $(UTILS_OUT_PATH)  $(FRAMEWORK_OUT_PATH)
EXPLORATION_ENV_OUT_BIN = ./bin/exploration_env.o
# ===========================================================================

# ==================== Battle Environment Definitions ==================
BATTLE_ENV_SRC_LIST = battle_gridworld/main.cpp battle_gridworld/battle_map.cpp battle_gridworld/battle_env.cpp battle_gridworld/battle_grid_agent.cpp
BATTLE_ENV_INC_LIST = -Ibattle_gridworld/include

BATTLE_ENV_DEPS = $(LOGGER_OUT_PATH) $(RECORDER_OUT) $(UTILS_OUT_PATH) $(FRAMEWORK_OUT_PATH)
BATTLE_ENV_OUT_BIN = ./bin/battle_env.o
# ===========================================================================

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
recorder:
	@echo Building Recorder
	g++ --std=c++11 $(RECORDER_INC_LIST)  -c $(RECORDER_SRC_LIST) -o $(RECORDER_OUT)
framework: logger utils recorder
	@echo Building Framework
	g++ --std=c++11 $(FRAMEWORK_FLAGS) $(FRAMEWORK_INC_LIST) $(LOGGER_INC_LIST) $(UTILS_INC_LIST) $(FRAMEWORK_SRC_LIST) -o $(FRAMEWORK_OUT_PATH)
	@echo Done

# The make recipe for the simple exploration based gridworld
exploration_gridworld: logger utils framework
	@echo Building Exploration Gridworld Example
	g++ --std=c++11 $(FRAMEWORK_INC_LIST) $(UTILS_INC_LIST) $(LOGGER_INC_LIST) $(EXPLORATION_ENV_INC_LIST) -o bin/run $(EXPLORATION_ENV_SRC_LIST) $(EXPLORATION_ENV_DEPS)

# The make recipe for the more complex battle-based gridworld
battle_gridworld: framework
	@echo Building Battle Gridworld Example
	g++ --std=c++11 $(FRAMEWORK_INC_LIST) $(UTILS_INC_LIST) $(LOGGER_INC_LIST) $(BATTLE_ENV_INC_LIST) -o bin/run $(BATTLE_ENV_SRC_LIST) $(BATTLE_ENV_DEPS)

battle: battle_gridworld

all: exploration_gridworld 


