
#include "CException.h"

namespace util {
CException::CException(const std::string& msg, int code)
    : std::runtime_error(msg),
      code_(code) {
}
}

