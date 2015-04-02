#pragma once

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
}
