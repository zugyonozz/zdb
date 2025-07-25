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
	type_void,
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

// === GET TYPE BY FLAG ===

template <typesFg fg = type_void> struct get_type_by_flag {
	using Type = void ;
	static Type* from(void* v) noexcept {
		return v ;
	}
} ;

template <> struct get_type_by_flag<type_uint8> {
	using Type = uint8 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_uint16> {
	using Type = uint16 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_uint32> {
	using Type = uint32 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_uint64> {
	using Type = uint64 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_uint128> {
	using Type = uint128 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_int8> {
	using Type = int8 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_int16> {
	using Type = int16 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_int32> {
	using Type = int32 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_int64> {
	using Type = int64 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_int128> {
	using Type = int128 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_float32> {
	using Type = float32 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_float64> {
	using Type = float64 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_float128> {
	using Type = float128 ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

template <> struct get_type_by_flag<type_varchar> {
	using Type = varchar ;
	static Type* from(void* v) noexcept {
		return static_cast<Type*>(v) ;
	}
} ;

// === SHORTCUT ===

template <typename T> constexpr bool is_integral_v = is_integral<T>::val ;

template <typename T> constexpr bool is_floating_point_v = is_floating_point<T>::val ;

template <typename T> constexpr bool is_arithmetic_v = is_arithmetic<T>::val ;

}

}