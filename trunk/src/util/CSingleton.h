
#pragma once

#include <memory>

namespace util {
template <typename T>
class CSingleton {
public:
    CSingleton() = delete;
    ~CSingleton() = delete;
    CSingleton(const CSingleton &) = delete;
    CSingleton(CSingleton &&) = delete;
    CSingleton& operator = (const CSingleton &) = delete;
    CSingleton& operator = (CSingleton &&) = delete;

    template <typename U>
    static void create(std::unique_ptr<U> u) {
        if (u.get() == nullptr)
            throw std::logic_error("CSingleton::create - null pointer");
        if (instance_.get() != nullptr)
            throw std::logic_error("CSingleton::create - already created");
        instance_ = std::move(u);
    }

    static T& instance() {
        if (instance_.get() == nullptr)
            throw std::logic_error("CSingleton::instance - not created");
        return *instance_;
    }
private:
    static std::unique_ptr<T> instance_;
};

template <typename T>
std::unique_ptr<T> CSingleton<T>::instance_;

}

