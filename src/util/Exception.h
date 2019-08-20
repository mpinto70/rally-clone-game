#pragma once

#include <stdexcept>
#include <string>

namespace util {
/** game exception. */
class Exception : public std::runtime_error {
public:
    /** creates the object.
     * @param msg the error message (accessible via what())
     * @param code the error code
     */
    Exception(const std::string& msg, int code);
    /** return the error code. */
    [[nodiscard]] int code() const { return code_; }

private:
    int code_; ///< error code
};
}
