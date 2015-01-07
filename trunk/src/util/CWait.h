
#ifndef CWAIT_RALLY
#define CWAIT_RALLY

#include <sys/time.h>
#include <cstdio>

namespace util {
/** Responsible for time lapse garantee. */
class CWait {
    public:
        /** creates object
         * @param milliseconds the minimum ammount of milliseconds to wait
         */
        CWait(size_t milliseconds);
        /** destructor. */
        ~CWait() = default;
        /** resets time count. */
        void reset();
        /** @returns se o tempo já expirou. */
        bool expired() const;
        /** wait until expires. */
        void wait() const;
        /** @returns the end. */
        const timeval & end() const { return end_; }
    private:
        size_t microseconds_;   ///< time to wait
        timeval end_;           ///< final time
};

}

#endif

