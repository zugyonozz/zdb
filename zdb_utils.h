#pragma once
#include "zdb_type_env.h"

namespace zdb {
namespace utils {

// SHORTCUT SPECIALIZE

template <typename T> constexpr bool is_integral_v = impl::is_integral<T>::val ;
template <typename T> constexpr bool is_floating_point_v = impl::is_floating_point<T>::val ;
template <typename T> constexpr bool is_text_v = impl::is_text<T>::val ;
template <typename T> constexpr bool is_arithmetic_v = is_integral_v<T> || is_floating_point_v<T> ;

// MOVE IMPLEMENTATION

template <typename T> constexpr impl::del_ref_t<T>&& move(T&& val) noexcept { return static_cast<impl::del_ref_t<T>&&>(val) ; }

}

}