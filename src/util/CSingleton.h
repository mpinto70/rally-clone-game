
#pragma once

#include <memory>

/** namespace of common tools. */
namespace util {
/** responsible for managing a singleton of \b T (may be polymorphic).*/
template <typename T>
class CSingleton {
    public:
        /** shall not be constructed nor copied. */
        CSingleton() = delete;
        /** shall not be constructed nor copied. */
        ~CSingleton() = delete;
        /** shall not be constructed nor copied. */
        CSingleton(const CSingleton &) = delete;
        /** shall not be constructed nor copied. */
        CSingleton(CSingleton &&) = delete;
        /** shall not be constructed nor copied. */
        CSingleton& operator = (const CSingleton &) = delete;
        /** shall not be constructed nor copied. */
        CSingleton& operator = (CSingleton &&) = delete;

        /** gets the instance of \b T geting a pointer to \b U (U must be derived from T).
         * @param u the unique pointer to \b U
         */
        template <typename U>
        static void create(std::unique_ptr<U> u) {
            if (u.get() == nullptr)
                throw std::logic_error("CSingleton::create - null pointer");
            if (instance_.get() != nullptr)
                throw std::logic_error("CSingleton::create - already created");
            instance_ = std::move(u);
        }

        /** destroys the instance. */
        static void destroy() {
            instance_.reset(nullptr);
        }

        /** gets the instance. */
        static T& instance() {
            if (instance_.get() == nullptr)
                throw std::logic_error("CSingleton::instance - not created");
            return *instance_;
        }
    private:
        static std::unique_ptr<T> instance_;    ///< the instance
};

template <typename T>
std::unique_ptr<T> CSingleton<T>::instance_;

}

