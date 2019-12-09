#include "include/gridenv.h"
#include "include/gridagent.h"
#include "utils.h"

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

void initAndSetupMPI(int argc, char **argv) {
    // One-time initialization
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &selfInfo.self_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &selfInfo.num_tasks);
    std::cout << "MPI Initialized for rank " << selfInfo.self_rank << std::endl;
}

void setupMsgLongPair() {
    constexpr int kLengthParticle = 1; // uint64_t, uint32_t
    MPI_Aint offsets[kLengthParticle], extent, lb;
    MPI_Datatype members[kLengthParticle];
    int counts[kLengthParticle];

    offsets[0] = 0;
    members[0] = MPI_INT;
    counts[0] = 2; // uint64_t

    // MPI_Type_get_extent(MPI_UNSIGNED_LONG_LONG, &lb, &extent);
    // offsets[1] = counts[0] * extent;
    // members[1] = MPI_UNSIGNED_LONG;
    // counts[1] = 1; // uint32_t

    MPI_Type_create_struct(kLengthParticle, counts, offsets, members, &MsgLongPair);
    MPI_Type_commit(&MsgLongPair);
}

void cleanUpMPI() {
    // MPI_Type_free(&MsgLongPair);
    MPI_Finalize();
}

int main(int argc, char** argv) {
  EnvBackend backend = EnvBackend::SEQ;

  int opt, fname_set=0, nodump=0;
  uint32_t width=WIDTH, height=HEIGHT, num_agents=NUM_AGENTS;
  uint32_t num_steps=NUM_STEPS, print_every=PRINT_EVERY;

  std::string filename = "dump.csv";

  while ((opt = getopt(argc, argv, "w:h:a:s:e:f:pmd")) != -1) {
      switch(opt) {
          case 'w': width = std::atoi(optarg); break;
          case 'h': height = std::atoi(optarg); break;
          case 'a': num_agents = std::atoi(optarg); break;
          case 's': num_steps = std::atoi(optarg); break;
          case 'e': print_every = std::atoi(optarg); break;
          case 'f': filename = optarg; fname_set=1; break;
          case 'p': backend = EnvBackend::OMP; break;
          case 'm': backend = EnvBackend::OMPI; break;
          case 'd': nodump=1; break;
          default:
                    std::cerr << "Unknown option " << opt << std::endl;
                    exit(-1);
      }
  }
  std::string type = (backend == EnvBackend::SEQ ? "seq" :
                      backend == EnvBackend::OMP ? "omp" : "mpi");
  if (!fname_set) {
      std::ostringstream fname;
      fname << type << "-a-" << num_agents/1000 << "k-s-" << float(num_steps)/1000
            << "k-g-" << width << "x" << height << ".csv";
      filename = fname.str();
  }
  filename = datadir + filename;

  const int kActionCount = GridAgentActions::COUNT;

  if (backend == EnvBackend::OMPI) {
      initAndSetupMPI(argc, argv);
  }

  if (backend != EnvBackend::OMPI || selfInfo.self_rank == kMPIMasterRank) {
      std::cout << "Running environment type " << type << std::endl
                << "Agents: " << num_agents << std::endl
                << "Steps: " << num_steps << std::endl
                << "Grid: " << height << "x" << width << std::endl
                << "Printing every " << print_every << " steps, ";
      if (nodump) std::cout << "NO DUMP FILE";
      else std::cout << "dump to " << filename;
      std::cout << std::endl << std::endl;
  }

  GridEnv env(width, height, num_agents, backend);

  std::vector<uint32_t> actions(num_agents, 0);
  for (int i = 0; i < num_steps; ++i) {
      if (i % print_every == 0
          && (backend != EnvBackend::OMPI || selfInfo.self_rank == kMPIMasterRank))
          std::cout << "At step " << i << std::endl;
      for (int j = 0; j < actions.size(); ++j)
          actions[j] = (std::rand() % kActionCount);
      const auto& rewards = env.step(actions);
  }

  if (selfInfo.self_rank == kMPIMasterRank) {
      if (!nodump) {
          std::cout << "Writing out dump file " << filename << std::endl;
          env.dump_data(header, filename, mode);
      }

      std::cout << std::endl << "Sample run finished";
  }

  if (backend == EnvBackend::OMPI) {
      cleanUpMPI();
  }

  return 0;
}
