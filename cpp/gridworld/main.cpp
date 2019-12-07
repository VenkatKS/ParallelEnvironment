#include "include/gridenv.h"
#include "include/gridagent.h"

#include <iostream>
#include <cstdlib>
#include <unistd.h>

constexpr char mode = 'w';
const std::vector<std::string> header = {"agent-action","agent-action-update","map-update","reward"};

constexpr int NUM_STEPS = 1000;
constexpr int NUM_AGENTS = 15000;
constexpr int PRINT_EVERY = 100;

int main(int argc, char** argv) {
  int opt;
  uint32_t width=10, height=10, num_agents=NUM_AGENTS;
  uint32_t num_steps=NUM_STEPS, print_every=PRINT_EVERY;
  std::string filename = "dump.csv";

  while ((opt = getopt(argc, argv, "w:h:a:s:p:f:")) != -1) {
      switch(opt) {
          case 'w': width = std::atoi(optarg);
                    break;
          case 'h': height = std::atoi(optarg);
                    break;
          case 'a': num_agents = std::atoi(optarg);
                    break;
          case 's': num_steps = std::atoi(optarg);
                    break;
          case 'p': print_every = std::atoi(optarg);
                    break;
          case 'f': filename = optarg;
                    break;
          default:
                    std::cerr << "Unknown option " << opt << std::endl;
                    exit(-1);
      }
  }

  const int kActionCount = GridAgentActions::COUNT;

  std::cout << "Running with" << std::endl
            << "Agents: " << num_agents << std::endl
            << "Steps: " << num_steps << std::endl
            << "Grid: " << height << "x" << width << std::endl
            << "Printing every " << print_every << " steps, dump to " << filename
            << std::endl << std::endl;

  GridEnv env(width, height, num_agents);

  std::vector<uint32_t> actions(num_agents, 0);
  std::cout << "Going to invoke step" << std::endl;
  for (int i = 0; i < num_steps; ++i) {
      if (i % print_every == 0) std::cout << "At step " << i << std::endl;
      for (int j = 0; j < actions.size(); ++j)
          actions[j] = (std::rand() % kActionCount);
      const auto& rewards = env.step(actions);
      // std::cout << std::endl << "Step " << i;
      // for (int reward : rewards) std::cout << " " << reward;
  }

  env.dump_data(header, std::string(filename), mode);

  std::cout << std::endl << "Sample run finished";
  return 0;
}
