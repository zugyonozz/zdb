#pragma once
#include <string>
#include "zdb_type_varchar.h"

namespace zdb {

using uint8 = unsigned char ;
using uint16 = unsigned short ;
using uint32 = unsigned ;
using uint64 = unsigned long ;
using uint128 = unsigned long long ;
using int8 = signed char ;
using int16 = signed short ;
using int32 = signed ;
using int64 = signed long ;
using int128 = signed long long ;
using float32 = float ;
using float64 = double ;
using float128 = long double ;
using text = std::string ;
template <unsigned I> using varchar = impl::constant_char<I> ;

namespace impl {

// INTEGRAL SPECIALIZE

// UNSIGNED SPECIALIZE

template <typename T> struct is_integral { static constexpr bool val = false ; } ;
template <> struct is_integral<uint8> { static constexpr bool val = true ; } ;
template <> struct is_integral<uint16> { static constexpr bool val = true ; } ;
template <> struct is_integral<uint32> { static constexpr bool val = true ; } ;
template <> struct is_integral<uint64> { static constexpr bool val = true ; } ;
template <> struct is_integral<uint128> { static constexpr bool val = true ; } ;

// SIGNED SPECIALIZE

template <> struct is_integral<int8> { static constexpr bool val = true ; } ;
template <> struct is_integral<int16> { static constexpr bool val = true ; } ;
template <> struct is_integral<int32> { static constexpr bool val = true ; } ;
template <> struct is_integral<int64> { static constexpr bool val = true ; } ;
template <> struct is_integral<int128> { static constexpr bool val = true ; } ;
template <> struct is_integral<char> { static constexpr bool val = true ; } ;
template <> struct is_integral<bool> { static constexpr bool val = true ; } ;

// FLOATING POINT SPECIALIZE

template <typename T> struct is_floating_point { static constexpr bool val = false ; } ;
template <> struct is_floating_point<float32> { static constexpr bool val = true ; } ;
template <> struct is_floating_point<float64> { static constexpr bool val = true ; } ;
template <> struct is_floating_point<float128> { static constexpr bool val = true ; } ;

// TEXT TYPES SPECIALIZE

template <typename T> struct is_text { static constexpr bool val = false ; } ;
template <unsigned I> struct is_text<varchar<I>> { static constexpr bool val = true ; } ;
template <> struct is_text<std::string> { static constexpr bool val = true ; } ;

// SEQUENCE IMPLEMENTATION

template <unsigned... Is> struct sequence {} ;
template <unsigned I, unsigned... Is> struct sequence_helper : sequence_helper<I - 1, I - 1, Is...> {} ;
template <unsigned... Is> struct sequence_helper<0, Is...> { using Type = sequence<Is...>; } ;
template <unsigned N> using make_sequence = typename sequence_helper<N>::Type ;
template <typename... Ts> using sequence_for = make_sequence<sizeof...(Ts)> ;

// DELETE REFERENCE IMPLEMENTATION

template <typename T> struct del_ref { using Type = T ; } ;
template <typename T> struct del_ref<T&> { using Type = T ; } ;
template <typename T> struct del_ref<T&&> { using Type = T ; } ;
template <typename T> using del_ref_t = typename del_ref<T>::Type ;

}

}