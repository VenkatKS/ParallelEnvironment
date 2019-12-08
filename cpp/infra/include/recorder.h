#ifndef _RECORDER_H
#define _RECORDER_H

#include <vector>
#include <string>
#include <chrono>

using timestamp_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
using duration_t = std::chrono::milliseconds;

class Recorder {
  public:
    void new_run();
    void start();
    void stop();

    void dump_data(const std::vector<std::string>& header, const std::string& filename, char mode);

  private:
    timestamp_t last_ts;
    std::vector<std::vector<duration_t>> _durations_by_run;
};

#endif
