#ifndef _LOGGER_H
#define _LOGGER_H

#include <string>
#include <vector>

class Logger {
public: 
  /* Reporting bitmasks */
  static const uint8_t   num_pipes = 4;
  
  /* INFO level */
  static const uint8_t   INFO = 1 << 0;
  static const char      *INFO_STR;
  
  /* WARN level */
  static const uint8_t   WARN = 1 << 1;
  static const char      *WARN_STR;
  
  /* Recoverable and Fatal ERR level */
  static const uint8_t   LERR = 1 << 2;
  static const char      *LERR_STR;

  static const uint8_t   FERR = 1 << 3;
  static const char      *FERR_STR;

  static const char      ALL = INFO | WARN | LERR | FERR;

  static const std::vector<uint8_t> avaliable_bitmasks;
  static const std::vector<const char *> bitmask_print;

  static void Initialize(std::string instance_name);
  static void Report(std::string msg, uint8_t sequence_bitmask);
  static void DumpPipes(uint8_t sequence_bitmask);

private:
  Logger();

  static std::vector<std::string> outbuf[Logger::num_pipes];
};

#endif
