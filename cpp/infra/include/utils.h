#ifndef _UTILS_H
#define _UTILS_H

#include "logger.h"

#include "mpi.h"
#include <random>
#include <vector>
#include <time.h>

constexpr int kMPIMasterRank = 0;

struct MPIInfo {
    int self_rank;
    int num_tasks;
    MPI_Status status;
};

extern MPIInfo selfInfo;
extern MPI_Datatype MsgLongPair;

class Utils {
};


class PathUtils{
};

class RandUtils : public Utils {
  private: 
    std::random_device device;
    std::mt19937 mt;

    static RandUtils *my_engine;

    RandUtils() { 
      ReseedEngine();
    }

  public:
    /* Return reference to Singleton */ 
    static RandUtils *GetEngine();
    
    /* Reseed Singleton */
    void ReseedEngine(uint32_t *seed = nullptr);
    
    /* Generate a random integer */

    /* NOTE. This constructs a distribution per call. Better performance can be
     * achieved by grouping calls by increasing count to a very high amount to
     * amortize the cost.
     */
    void UniformRandomIntegers(uint32_t a, uint32_t b, uint32_t count, std::vector<uint32_t> &bufp);
};
#endif
