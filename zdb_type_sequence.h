#pragma once

namespace zdb {

namespace impl{

// SEQUENCE IMPLEMENTATION

template <unsigned... Is> struct sequence {} ;
template <unsigned I, unsigned... Is> struct sequence_helper : sequence_helper<I - 1, I - 1, Is...> {} ;
template <unsigned... Is> struct sequence_helper<0, Is...> { using Type = sequence<Is...>; } ;
template <unsigned N> using make_sequence = typename sequence_helper<N>::Type ;
template <typename... Ts> using sequence_for = make_sequence<sizeof...(Ts)> ;

}

}