#pragma once

namespace zdb {

namespace impl {

// DELETE REFERENCE IMPLEMENTATION

template <typename T> struct del_ref { using Type = T ; } ;
template <typename T> struct del_ref<T&> { using Type = T ; } ;
template <typename T> struct del_ref<T&&> { using Type = T ; } ;
template <typename T> using del_ref_t = typename del_ref<T>::Type ;

}

namespace utils {

// MOVE IMPLEMENTATION

template <typename T> constexpr impl::del_ref_t<T>&& move(T&& val) noexcept { return static_cast<impl::del_ref_t<T>&&>(val) ; }

}

}