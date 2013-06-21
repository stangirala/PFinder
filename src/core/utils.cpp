#include <ios>
#include <iostream>
#include <string.h>
#include <sstream> // for stringbuf

#include "utils.h"

state_t Log::DEBUG = OFF;
std::ios *Log::stream = nullptr;

void Log::log_msg(char *msg) {

  if (DEBUG == ON) {
    //stream << "LOG_MSG: " << msg << std::endl;
    stream << "LOG_MSG: ";
  }
}

Log::Log(state_t state, char *stream) {

  if (DEBUG != ON) {
    DEBUG = state;
  }

  if (Log::stream != nullptr) {
    if (strcmp(stream, "cout") == 0) {
      std::stringbuf *buffer = new std::stringbuf();
      Log::stream = new std::iostream(buffer);
    }
  }
}

