#pragma once

#include <memory>

/** namespace of common tools. */
namespace util {
/** responsible for managing a singleton of \b T (may be polymorphic).*/
template <typename T>
class Singleton {
public:
    /** shall not be constructed nor copied. */
    Singleton() = delete;
    /** shall not be constructed nor copied. */
    ~Singleton() = delete;
    /** shall not be constructed nor copied. */
    Singleton(const Singleton&) = delete;
    /** shall not be constructed nor copied. */
    Singleton(Singleton&&) = delete;
    /** shall not be constructed nor copied. */
    Singleton& operator=(const Singleton&) = delete;
    /** shall not be constructed nor copied. */
    Singleton& operator=(Singleton&&) = delete;

    /** gets the instance of \b T getting a pointer to \b U (U must be derived from T).
     * @param u the unique pointer to \b U
     */
    template <typename U>
    static void create(std::unique_ptr<U> u) {
        if (u.get() == nullptr) {
            throw std::logic_error("Singleton::create - null pointer");
        }
        if (instance_.get() != nullptr) {
            throw std::logic_error("Singleton::create - already created");
        }
        instance_ = std::move(u);
    }

    /** destroys the instance. */
    static void destroy() {
        instance_.reset(nullptr);
    }

    /** gets the instance. */
    static T& instance() {
        if (instance_.get() == nullptr) {
            throw std::logic_error("Singleton::instance - not created");
        }
        return *instance_;
    }

private:
    static std::unique_ptr<T> instance_; ///< the instance
};

template <typename T>
std::unique_ptr<T> Singleton<T>::instance_;
}
