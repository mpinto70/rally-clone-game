
#include "CWait.h"

#include <unistd.h>

namespace util {

CWait::CWait(const size_t milliseconds)
    : microseconds_(milliseconds * 1000),
      end_ {0, 0} {
    reset();
}

static constexpr suseconds_t MILLION = 1000 * 1000;

void CWait::reset() {
    gettimeofday(&end_, nullptr);
    end_.tv_usec += microseconds_;
    if (end_.tv_usec > MILLION) {
        const auto leftover = end_.tv_usec / MILLION;
        end_.tv_sec += leftover;
        end_.tv_usec %= MILLION;
    }
}

bool CWait::expired() const {
    timeval t;
    gettimeofday(&t, nullptr);
    if (t.tv_sec > end_.tv_sec) return true;
    if (t.tv_sec < end_.tv_sec) return false;
    return (t.tv_usec >= end_.tv_usec);
}

void CWait::wait() const {
    while (not expired()) {
        usleep(200);
    }
}

}

