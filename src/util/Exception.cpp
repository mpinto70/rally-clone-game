#include "Exception.h"

namespace util {
Exception::Exception(const std::string& msg, int code)
      : std::runtime_error(msg),
        code_(code) {
}
}
