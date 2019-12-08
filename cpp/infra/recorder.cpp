#include "include/recorder.h"

#include <fstream>

static timestamp_t get_timestamp() {
  return std::chrono::high_resolution_clock::now();
}

void Recorder::new_run() {
    _durations_by_run.push_back(std::vector<duration_t>{});
}

void Recorder::start() {
    last_ts = get_timestamp();
}

void Recorder::stop() {
    timestamp_t cur_ts = get_timestamp();
    auto duration = std::chrono::duration_cast<duration_t>(cur_ts-last_ts);
    _durations_by_run.back().push_back(duration);
}

void Recorder::dump_data(const std::vector<std::string>& header, const std::string& filename, char mode) {
    std::ofstream outfile;
    auto mode_bits = std::ofstream::out;
    if (mode == 'w') mode_bits |= std::ofstream::trunc;
    else mode_bits |= std::ofstream::app;

    outfile.open(filename, mode_bits);
    for (const auto& colname : header)
        outfile << colname << ",";
    outfile << "sum" << std::endl;
    
    for (const auto& record : _durations_by_run) {
        bool set = false;
        duration_t total_duration;
        for (const auto& val : record) {
            if (!set) {
                set = true;
                total_duration = val;
            } else total_duration += val;
            outfile << val.count() << ",";
        }
        outfile << total_duration.count() << std::endl;
    }
}
