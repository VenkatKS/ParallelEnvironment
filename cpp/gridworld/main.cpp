#include "include/gridenv.h"
#include "include/gridagent.h"

#include <iostream>
#include <cstdlib>

constexpr int NUM_STEPS = 1000;
constexpr int NUM_AGENTS = 200;

int main() {
  const uint32_t width=10, height=10, num_agents=NUM_AGENTS;
  const int kActionCount = GridAgentActions::COUNT;

  std::cout << "Starting env creation" << std::endl;
  GridEnv env(width, height, num_agents);

  std::vector<uint32_t> actions(num_agents, 0);
  std::cout << "Going to invoke step" << std::endl;
  for (int i = 0; i < NUM_STEPS; ++i) {
      for (int j = 0; j < actions.size(); ++j)
          actions[j] = (std::rand() % kActionCount);
      const auto& rewards = env.step(actions);
      // std::cout << std::endl << "Step " << i;
      // for (int reward : rewards) std::cout << " " << reward;
  }

  std::cout << std::endl << "Sample run finished";
  return 0;
}
