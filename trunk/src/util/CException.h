
#pragma once

#include <stdexcept>
#include <string>

namespace util {
class CException : public std::runtime_error {
    public:
        CException(const std::string & msg, int code);
        int code() const { return code_; }
    private:
        int code_;
};

}
