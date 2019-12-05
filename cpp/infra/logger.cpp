#include "logger.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

const char* Logger::INFO_STR = "INFO";
const char* Logger::WARN_STR = "WARN";
const char* Logger::LERR_STR = "LERR";
const char* Logger::FERR_STR = "FERR";

const std::vector<uint8_t> Logger::avaliable_bitmasks = { Logger::INFO, Logger::WARN,\
                                                    Logger::LERR, Logger::FERR };
const std::vector<const char*> Logger::bitmask_print = { Logger::INFO_STR,\
                                                   Logger::WARN_STR,\
                                                   Logger::LERR_STR,\
                                                   Logger::FERR_STR };
std::vector<std::string> Logger::outbuf[Logger::num_pipes];


void Logger::Initialize(std::string instance_name) {
  std::stringstream strout;

  strout << "Logger Initialized For: " << instance_name << std::endl;

  Report(strout.str(), INFO);
}

void Logger::Report(std::string msg, uint8_t sequence_bitmask) {
  uint8_t idx = 0;

  while (sequence_bitmask) {
    if (sequence_bitmask & 1)
      Logger::outbuf[idx].push_back(msg);

    sequence_bitmask >>= 1;
  }

  return;
}

void Logger::DumpPipes(uint8_t sequence_bitmask) {
  uint8_t idx = 0;
  while (sequence_bitmask && idx < num_pipes) {
    if (sequence_bitmask & 1) {
      while (Logger::outbuf[idx].size() > 0) {
        std::string item = Logger::outbuf[idx].back();
        Logger::outbuf[idx].pop_back();
        std::cout << "[" << bitmask_print[idx] << "]" << item;
      }
    }
    sequence_bitmask >>= 1;
  }
  return;
}




