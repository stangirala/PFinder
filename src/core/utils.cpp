#include <ostream>
#include <iostream>
#include <string>
#include <sstream> // for stringbuf

#include "utils.h"

state_t Log::DEBUG = OFF;
std::ostream *Log::stream_ptr = nullptr;

void Log::log_msg(std::string msg) {

  if (DEBUG == ON) {
    *(stream_ptr) << "LOG_MSG: " << msg << std::endl;
  }
}

Log::Log(state_t state, std::string stream) {

  if (DEBUG != ON) {
    DEBUG = state;
  }

  if (stream_ptr == nullptr) {
    if (stream == "cout") {
      std::streambuf *buffer = std::cout.rdbuf();
      Log::stream_ptr = new std::iostream(buffer);
    }
  }

}

