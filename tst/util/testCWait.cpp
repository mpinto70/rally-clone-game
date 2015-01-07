
#include "testCWait.h"

#include "util/CWait.h"

#include <sys/time.h>
#include <utility>

bool operator < (const timeval & lhs, const timeval & rhs) {
    if (lhs.tv_sec < rhs.tv_sec) return true;
    if (lhs.tv_sec > rhs.tv_sec) return false;
    return lhs.tv_usec < rhs.tv_usec;
}

static constexpr suseconds_t MILHAO = 1000 * 1000;
timeval operator + (timeval lhs, const size_t milli) {
    lhs.tv_usec += milli * 1000;
    if (lhs.tv_usec > MILHAO) {
        lhs.tv_sec += lhs.tv_usec / MILHAO;
        lhs.tv_usec %= MILHAO;
    }
    return lhs;
}

double operator - (const timeval & lhs, const timeval & rhs) {
    const int dsec = (lhs.tv_sec - rhs.tv_sec) * (int) MILHAO;
    const int dusec = lhs.tv_usec - rhs.tv_usec;
    return (dsec + dusec) / 1000.0;
}

namespace util {
namespace tst {

static void print(const std::string & id,
                  const timeval & val) {
    printf("%15s = %8ld / %8ld\n", id.c_str(), val.tv_sec, val.tv_usec);
}

static void print(const int line,
                  const size_t milli,
                  const timeval & after,
                  const timeval & end) {
    printf("\n");
    printf("from line = %d\n", line);
    printf("size of wait = %zu\n", milli);
    print("after", after);
    print("end", end);
    printf("diff = %lf\n", end - after);
}

static void verifyWait(const size_t milli) {
    using namespace std::rel_ops;
    timeval after;

    CWait obj(milli);
    auto end = obj.end();
    for (size_t i = 0; i < 10; ++i) {
        TSM_ASSERT(milli, not obj.expired());
    }
    obj.wait();
    TSM_ASSERT(milli, obj.expired());
    gettimeofday(&after, nullptr);
    TSM_ASSERT(milli, end <= after);
    if (end > after)
        print(__LINE__, milli, after, end);

    obj.reset();
    end = obj.end();
    for (size_t i = 0; i < 10; ++i) {
        TSM_ASSERT(milli, not obj.expired());
    }
    obj.wait();
    TSM_ASSERT(milli, obj.expired());
    gettimeofday(&after, nullptr);

    TSM_ASSERT(milli, end <= after);
    if (end > after)
        print(__LINE__, milli, after, end);
}

void TestCWait::testWait() {
    for (size_t i = 0; i < 10; ++i) {
        verifyWait(1);
        verifyWait(10);
        verifyWait(20);
        verifyWait(30);
    }
}

static void verifyEnd(const size_t milli) {
    using namespace std::rel_ops;
    timeval before;

    gettimeofday(&before, nullptr);
    CWait obj(milli);
    auto end = before + milli;
    TSM_ASSERT(milli, before < obj.end());
    TSM_ASSERT(milli, end <= obj.end());

    gettimeofday(&before, nullptr);
    obj.reset();
    end = before + milli;
    TSM_ASSERT(milli, before < obj.end());
    TSM_ASSERT(milli, end <= obj.end());
}

void TestCWait::testEnd() {
    for (size_t i = 0; i < 1000; ++i) {
        verifyEnd(1);
        verifyEnd(10);
        verifyEnd(20);
        verifyEnd(30);
    }
}

}
}

