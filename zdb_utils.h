#pragma once
#include "zdb_type_env.h"

namespace zdb {
namespace utils {

// MOVE IMPLEMENTATION

template <typename T> constexpr impl::del_ref_t<T>&& move(T&& val) noexcept { return static_cast<impl::del_ref_t<T>&&>(val) ; }

}

}