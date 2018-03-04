#pragma once

#include <cstdio>
#include <sys/time.h>

namespace util {
/** responsible for time lapse garantee. */
class Wait {
public:
    /** creates object
     * @param milliseconds the minimum ammount of milliseconds to wait
     */
    Wait(size_t milliseconds);
    /** destructor. */
    ~Wait() = default;
    /** resets time count. */
    void reset();
    /** @returns se o tempo já expirou. */
    bool expired() const;
    /** wait until expires. */
    void wait() const;
    /** @returns the end. */
    const timeval& end() const { return end_; }

private:
    size_t microseconds_; ///< time to wait
    timeval end_;         ///< final time
};
}
