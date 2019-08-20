#pragma once

#include <cstdio>
#include <sys/time.h>

namespace util {
/** responsible for time lapse guarantee. */
class Wait {
public:
    /** creates object
     * @param milliseconds the minimum amount of milliseconds to wait
     */
    explicit Wait(size_t milliseconds);
    /** resets time count. */
    void reset();
    /** @returns if time is expired. */
    [[nodiscard]] bool expired() const;
    /** wait until expires. */
    void wait() const;
    /** @returns the end. */
    [[nodiscard]] const timeval& end() const { return end_; }

private:
    size_t microseconds_; ///< time to wait
    timeval end_;         ///< final time
};
}
