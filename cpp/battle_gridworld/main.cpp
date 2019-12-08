#include "battle_env.h"
#include "battle_grid_agent.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>

constexpr char mode = 'w';
const std::vector<std::string> header = {"agent-action",
                                         "agent-action-update",
                                         "map-update",
                                         "reward"};
// Defaults
const std::string datadir = "data/";
constexpr int NUM_STEPS = 1000;
constexpr int NUM_AGENTS = 15000;
constexpr int PRINT_EVERY = 100;
constexpr int WIDTH=1000, HEIGHT=1000;

int main(int argc, char** argv) {
  EnvBackend backend = EnvBackend::SEQ;

  int opt, fname_set=0, nodump=0;
  uint32_t width=WIDTH, height=HEIGHT, num_agents=NUM_AGENTS;
  uint32_t num_steps=NUM_STEPS, print_every=PRINT_EVERY;

  std::string filename = "dump.csv";

  while ((opt = getopt(argc, argv, "w:h:a:s:e:f:pd")) != -1) {
      switch(opt) {
          case 'w': width = std::atoi(optarg); break;
          case 'h': height = std::atoi(optarg); break;
          case 'a': num_agents = std::atoi(optarg); break;
          case 's': num_steps = std::atoi(optarg); break;
          case 'e': print_every = std::atoi(optarg); break;
          case 'f': filename = optarg; fname_set=1; break;
          case 'p': backend = EnvBackend::OMP; break;
          case 'd': nodump=1; break;
          default:
                    std::cerr << "Unknown option " << opt << std::endl;
                    exit(-1);
      }
  }
  std::string type = (backend == EnvBackend::SEQ ? "seq" : "omp");
  if (!fname_set) {
      std::ostringstream fname;
      fname << type << "-a-" << num_agents/1000 << "k-s-" << float(num_steps)/1000
            << "k-g-" << width << "x" << height << ".csv";
      filename = fname.str();
  }
  filename = datadir + filename;

  const int kActionCount = BattleGridAgentActions::COUNT;

  std::cout << "Running environment type " << type << std::endl
            << "Agents: " << num_agents << std::endl
            << "Steps: " << num_steps << std::endl
            << "Grid: " << height << "x" << width << std::endl
            << "Printing every " << print_every << " steps, ";
  if (nodump) std::cout << "NO DUMP FILE";
  else std::cout << "dump to " << filename;
  std::cout << std::endl << std::endl;

  /* Construct the proper environments here */
  BattleEnv env(width, height, num_agents, backend);

  std::vector<uint32_t> actions(num_agents, 0);
  std::cout << "Going to invoke step" << std::endl;
  for (int i = 0; i < num_steps; ++i) {
      if (i % print_every == 0) std::cout << "At step " << i << std::endl;
      for (int j = 0; j < actions.size(); ++j)
          actions[j] = (std::rand() % kActionCount);
      const auto& rewards = env.step(actions);
  }

  if (!nodump) {
      std::cout << "Writing out dump file " << filename << std::endl;
      env.dump_data(header, filename, mode);
  }

  std::cout << std::endl << "Sample run finished";
  return 0;
}
