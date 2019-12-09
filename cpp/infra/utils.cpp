#include "utils.h"
#include <vector>
#include <sstream>

MPIInfo selfInfo;
MPI_Datatype MsgLongPair;

RandUtils *RandUtils::my_engine = nullptr;

RandUtils *RandUtils::GetEngine() {
  if (my_engine == nullptr) {
    my_engine = new RandUtils();
  }

  return my_engine;
}

void RandUtils::ReseedEngine(uint32_t *seed) {
      if (seed != nullptr) {
        /* Report reseeding to the user */
        std::stringstream logger_msg;
        logger_msg << "[RAND] Reseeded Random Engine with " << seed << std::endl;
        Logger::Report (logger_msg.str(), Logger::INFO | Logger::WARN);
        mt.seed(*seed);
      } else {
        mt.seed(device());
        Logger::Report("[RAND] Reseeded Random Engine with Entropy.", Logger::INFO | Logger::WARN);
      }
      return;
}

void RandUtils::UniformRandomIntegers(uint32_t a, uint32_t b, uint32_t count, std::vector<uint32_t> &bufp) {
  std::uniform_int_distribution<int> distribution(a,b);
  
  for (int i = 0; i < count; i ++) {
    bufp.push_back(distribution(mt));
  }

  return;
}

