#pragma once

#include <stdexcept>
#include <string>
#include <typeinfo>

namespace util {

template< typename T >
class CEnumIterator {
    public:
        typedef typename std::underlying_type<T>::type enumType;
        class Iterator {
            public:
                Iterator(enumType value)
                    : value_(value) {
                }

                T operator*() const {
                    return (T)value_;
                }

                void operator++(void) {
                    ++value_;
                }

                bool operator!=(Iterator rhs) {
                    return value_ != rhs.value_;
                }

            private:
                enumType value_;
        };

};

template< typename T >
typename CEnumIterator<T>::Iterator begin(CEnumIterator<T>) {
    return typename CEnumIterator<T>::Iterator((typename CEnumIterator<T>::enumType) T::FIRST);
}

template< typename T >
typename CEnumIterator<T>::Iterator end(CEnumIterator<T>) {
    return typename CEnumIterator<T>::Iterator((typename CEnumIterator<T>::enumType) T::LAST);
}

template <typename E, typename T>
E to_Enum(T t) {
    constexpr T first = static_cast<T>(E::FIRST);
    constexpr T last = static_cast<T>(E::LAST);
    if (t < first || t >= last) {
        throw std::invalid_argument("to_Enum of "
                                    + std::string(typeid(E).name())
                                    + " - out of range ("
                                    + std::to_string(t)
                                    + ")");
    }
    return static_cast<E>(t);
}

template <typename T, typename E>
T from_Enum(E e) {
    return static_cast<T>(e);
}

}
