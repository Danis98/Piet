#ifndef PIET_UTIL_ENUM_CAST_H
#define PIET_UTIL_ENUM_CAST_H

#include <type_traits>

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

template <typename T>
concept derived_integral = std::is_integral<std::underlying_type<T>::type>;

#endif