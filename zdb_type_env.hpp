#pragma once

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
using varchar = const char* ;

enum typesFg : uint8 {
	type_uint8,
	type_uint16,
	type_uint32,
	type_uint64,
	type_uint128,
	type_int8,
	type_int16,
	type_int32,
	type_int64,
	type_int128,
	type_float32,
	type_float64,
	type_float128,
	type_varchar,
} ;

namespace utils {
// === INTEGRAL ===

// === UNSIGNED ===

template <typename T> struct is_integral {
	static constexpr bool val = false ;
} ;

template <> struct is_integral<uint8> {
	static constexpr bool val = true ;
} ;

template <> struct is_integral<uint16> {
	static constexpr bool val = true ;
} ;

template <> struct is_integral<uint32> {
	static constexpr bool val = true ;
} ;

template <> struct is_integral<uint64> {
	static constexpr bool val = true ;
} ;

template <> struct is_integral<uint128> {
	static constexpr bool val = true ;
} ;

// === SIGNED ===

template <> struct is_integral<int8> {
	static constexpr bool val = true ;
} ;

template <> struct is_integral<int16> {
	static constexpr bool val = true ;
} ;

template <> struct is_integral<int32> {
	static constexpr bool val = true ;
} ;

template <> struct is_integral<int64> {
	static constexpr bool val = true ;
} ;

template <> struct is_integral<int128> {
	static constexpr bool val = true ;
} ;

template <> struct is_integral<char> {
	static constexpr bool val = true ;
} ;

template <> struct is_integral<bool> {
	static constexpr bool val = true ;
} ;

// === FLOATING POINT ===

template <typename T> struct is_floating_point {
	static constexpr bool val = false ;
} ;

template <> struct is_floating_point<float32> {
	static constexpr bool val = true ;
} ;

template <> struct is_floating_point<float64> {
	static constexpr bool val = true ;
} ;

template <> struct is_floating_point<float128> {
	static constexpr bool val = true ;
} ;

// === ARITHMETIC ===

template <typename T> struct is_arithmetic {
	static constexpr bool val = is_integral<T>::val || is_floating_point<T>::val ;
} ;

// === getTypeByFlag ===

template <typesFg fg> struct getTypeByFlag {} ;

template <> struct getTypeByFlag<type_uint8> {
	using type = uint8 ;
} ;

template <> struct getTypeByFlag<type_uint16> {
	using type = uint16 ;
} ;

template <> struct getTypeByFlag<type_uint32> {
	using type = uint32 ;
} ;

template <> struct getTypeByFlag<type_uint64> {
	using type = uint64 ;
} ;

template <> struct getTypeByFlag<type_uint128> {
	using type = uint128 ;
} ;

template <> struct getTypeByFlag<type_int8> {
	using type = int8 ;
} ;

template <> struct getTypeByFlag<type_int16> {
	using type = int16 ;
} ;

template <> struct getTypeByFlag<type_int32> {
	using type = int32 ;
} ;

template <> struct getTypeByFlag<type_int64> {
	using type = int64 ;
} ;

template <> struct getTypeByFlag<type_int128> {
	using type = int128 ;
} ;

template <> struct getTypeByFlag<type_float32> {
	using type = float32 ;
} ;

template <> struct getTypeByFlag<type_float64> {
	using type = float64 ;
} ;

template <> struct getTypeByFlag<type_float128> {
	using type = float128 ;
} ;

template <> struct getTypeByFlag<type_varchar> {
	using type = varchar ;
} ;

// === SHORTCUT ===

template <typename T> constexpr bool is_integral_v = is_integral<T>::val ;

template <typename T> constexpr bool is_floating_point_v = is_floating_point<T>::val ;

template <typename T> constexpr bool is_arithmetic_v = is_arithmetic<T>::val ;

template <typesFg typesFg> using getTypeByFlag_v = typename getTypeByFlag<typesFg>::type ;

}

}