#pragma once
#include "zdb_utils.h"

namespace zdb {

namespace error_handler {

struct out_of_node_range { const char* operator()() { return "Node index oyt of range!" ; } ; } ;

}

namespace impl {

// TABLE IMPLEMENTATION

template <unsigned I, typename T> struct Tuple_id ;

template <unsigned I, typename T> class Node {
	static_assert(utils::is_defined<T>, "undefined type!") ;

protected :
	T* val ;
	unsigned size_, cap_ ;

public :
	Node() noexcept : val(nullptr), size_(0), cap_(0) {}
	Node(const T& val) noexcept : size_(1), cap_(1) { val = new T[cap_] ; this->val[0] = val ; }
	Node(T&& val) noexcept : size_(1), cap_(1) { val = new T[cap_] ; this->val[0] = utils::move(val) ; }
	Node(Node&& o) noexcept : val(utils::move(o.val)), size_(o.size_), cap_(o.cap_) { o.size_ = o.cap_ = 0 ; }

	Node(const Node& o) noexcept : size_(o.size_), cap_(o.cap_) {
		this->val = new T[o.cap_] ;
		for(unsigned i = 0; i < size_; i++) this->val[i] = o.val[i] ;
	}

	~Node() noexcept { delete [] val ; }

	Node& operator=(const Node& o) noexcept {
		if(this == &o) return *this ;
		delete [] val ;
		size_ = o.size_ ;
		cap_ = o.cap_ ;
		val = new T[o.cap_] ;
		for(unsigned i = 0; i < size_; i++) val[i] = o.val[i] ;
		return *this ;
	}

	Node& operator=(Node&& o) noexcept {
		if(this == &o) return *this ;
		delete [] val ;
		size_ = o.size_ ;
		cap_ = o.cap_ ;
		val = o.val ;
		o.val = nullptr ;
		o.size_ = o.cap_ = 0 ;
		return *this ;
	}

	T& operator[](unsigned idx) { if (idx >= size_) throw error_handler::out_of_node_range() ; return val[idx] ; }
	const T& operator[](unsigned idx) const { if (idx >= size_) throw error_handler::out_of_node_range() ; return val[idx] ; }
	T* data(unsigned idx) { if(idx >= size_) throw error_handler::out_of_node_range() ; return &val[idx] ; }
	unsigned size() const noexcept { return size_ ; }
	unsigned cap() const noexcept { return cap_ ; }

	Node& reserve(unsigned newCap) noexcept {
		if (newCap <= cap_) return *this ;
		T* tmp = new T[newCap] ;
		for (unsigned i = 0; i < size_; i++) tmp[i] = val[i] ;
		delete [] val ;
		val = tmp ;
		cap_ = newCap ;
		return *this ;
	}

	Node& push(const T& val) noexcept {
		if(size_ == cap_) reserve(cap_ + (cap_ / 2) + 1) ;
		val[size_] = val ;
		++size_ ;
		return *this ;
	}

	Node& erase(unsigned idx) {
		if (idx >= size_) throw error_handler::out_of_node_range() ;
        for (unsigned i = idx; i < size_ - 1; ++i) val[i] = val[i + 1] ;
        --size_ ;
        return *this;
	}

	Node& pop() noexcept { --size_ ; return *this ;}

    Node& shrink_to_fit() {
        if (size_ == cap_) return *this ;
        T* tmp = new T[size_] ;
        for (unsigned i = 0; i < size_; i++) tmp[i] = val[i] ;
        delete[] val ;
        val = tmp;
        cap_ = size_;
        return *this;
    }

	T& get() noexcept { return val ; }
	const T& get() const noexcept { return val ; }
	Node& set(const T& val) noexcept { this->val = val ; return *this ; }
	T* begin() noexcept { return val ; }
	T* end() noexcept { return val + size_ ; }
	const T* begin() const noexcept { return val ; }
	const T* end() const noexcept { return val + size_ ; }
} ;

template <typename Sequence, typename ... Ts> class Tuple_impl ;
template <unsigned I, typename T, typename ... Ts> struct Tuple_id<I, Tuple_impl<T, Ts...>> : Tuple_id<I - 1, Tuple_impl<Ts...>> {} ;
template <typename T, typename ... Ts> struct Tuple_id<0, Tuple_impl<T, Ts...>> { using Type = T ; } ;
template <unsigned I, typename ... Ts> using Tuple_id_t = typename Tuple_id<I, Ts...>::Type ;
template <unsigned ... Is, typename ... Ts> class Tuple_impl<sequence<Is...>, Ts...> : private Node<Is, Ts>... {
public :
	Tuple_impl() noexcept = default ;
	Tuple_impl(const Ts&... args) noexcept : Node<Is, Ts>(args)... {}
	Tuple_impl(Ts&&... args) noexcept : Node<Is, Ts>(utils::move(args))... {}

	template <unsigned I> decltype(auto) get() noexcept { return static_cast<Node<I, Tuple_id_t<I, Tuple_impl<Ts...>>>&>(*this).get() ; }
	template <unsigned I> decltype(auto) get() const noexcept { return static_cast<const Node<I, Tuple_id_t<I, Tuple_impl<Ts...>>>&>(*this).get() ; }
	template <unsigned Row> Tuple_impl& getRow() noexcept { return { get<sequence<Is...>>()[Row]...} ; }
} ;

}

template <typename ... Ts> using Tuple = impl::Tuple_impl<impl::sequence_for<Ts...>, Ts...> ;

}