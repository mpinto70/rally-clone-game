#pragma once

#include <stdexcept>
#include <string>
#include <typeinfo>

/** define to be used on enum's to_string functions. */
#define CASE_ENUM_TO_STRING(VALUE) \
    case VALUE: return #VALUE

namespace util {

template <typename T>
class EnumIterator {
public:
    typedef typename std::underlying_type<T>::type enumType;
    class Iterator {
    public:
        Iterator(enumType value)
              : value_(value) {
        }

        T operator*() const {
            return (T) value_;
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

template <typename T>
typename EnumIterator<T>::Iterator begin(EnumIterator<T>) {
    return typename EnumIterator<T>::Iterator((typename EnumIterator<T>::enumType) T::FIRST);
}

template <typename T>
typename EnumIterator<T>::Iterator end(EnumIterator<T>) {
    return typename EnumIterator<T>::Iterator((typename EnumIterator<T>::enumType) T::LAST);
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

template <typename T>
bool isValid(T t) {
    return t >= T::FIRST && t < T::LAST;
}

template <typename T>
void validate(T t) {
    if (not isValid(t)) {
        const auto val = from_Enum<int>(t);
        const std::string msg = std::string(typeid(T).name()) + " - invalid value " + to_string(val);
        throw Exception(msg, val);
    }
}
}
