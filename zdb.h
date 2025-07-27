#pragma once
#include "zdb_utils.h"
#include "zdb_type_date.h"

namespace zdb {

namespace error_handler {

struct out_of_node_range { const char* operator()() const noexcept { return "Node index out of range!" ; } ; } ;

}

namespace utils {

template <typename T> constexpr bool is_defined = is_arithmetic_v<T> || is_text_v<T> || is_date_v<T> ;

}

namespace impl {

// TABLE IMPLEMENTATION

template <unsigned I, typename T> class Node {
private :
	static_assert(utils::is_defined<T>, "undefined type!") ;

	Node& swap(Node& o) noexcept {
		swap(data_, o.data_) ;
		swap(size_, size_) ;
		swap(cap_, cap_) ;
	}

protected :
	T* data_ ;
	unsigned size_ ; 
	unsigned cap_ ;

public :
	Node() noexcept : data_(nullptr), size_(0), cap_(0) {}
	
	Node(const T& val) : size_(1), cap_(1) { 
		try {
			data_ = new T[cap_] ;
			this->data_[0] = val ;
		} catch (...) {
			delete [] data_ ;
			throw ;
		}
	}
	Node(T&& val) noexcept : size_(1), cap_(1) { 
		data_ = new T[cap_] ; 
		this->data_[0] = utils::move(val) ; 
	}
	
	Node(Node&& o) noexcept : data_(o.data_), size_(o.size_), cap_(o.cap_) { 
		o.data_ = nullptr ; 
		o.size_ = o.cap_ = 0 ; 
	}

	Node(const Node& o) noexcept : size_(o.size_), cap_(o.cap_) { 
		this->data_ = new T[o.cap_] ; 
		for(unsigned i = 0; i < size_; i++) 
		this->data_[i] = o.data_[i] ; 
	}
	
	~Node() noexcept { delete [] data_ ; }

	Node& operator=(const Node& o) noexcept {
		if(this == &o) 
			return *this ;
		Node tmp(o) ;
		swap(tmp) ;
		return *this ;
	}

	Node& operator=(Node&& o) {
		if(this == &o) 
			return *this ;
		delete [] data_ ;
		size_ = o.size_ ;
		cap_ = o.cap_ ;
		data_ = o.data_ ;
		o.data_ = nullptr ;
		o.size_ = o.cap_ = 0 ;
		return *this ;
	}

	T& operator[](unsigned idx) { 
		if (idx >= size_) 
			throw error_handler::out_of_node_range() ; 
		return data_[idx] ; 
	}

	const T& operator[](unsigned idx) const { 
		if (idx >= size_) 
			throw error_handler::out_of_node_range() ; 
		return data_[idx] ; 
	}

	T* data(unsigned idx) { 
		if(idx >= size_) 
			throw error_handler::out_of_node_range() ; 
		return &data_[idx] ; 
	}

	unsigned size() const noexcept { 
		return size_ ; 
	}

	unsigned cap() const noexcept { 
		return cap_ ; 
	}

	void reserve(unsigned newCap) noexcept {
		if (newCap <= cap_) 
			return ;
		T* tmp = new T[newCap] ;
		for (unsigned i = 0; i < size_; i++) 
			tmp[i] = data_[i] ;
		delete [] data_ ;
		data_ = tmp ;
		cap_ = newCap ;
	}

	void push(const T& val) noexcept {
		if(size_ == cap_) 
			reserve(cap_ == 0 ? 1 : cap_ * 2) ;
		data_[size_] = val ;
		++size_ ;
		return *this ;
	}

	void push(T&& val) noexcept {
		if(size_ == cap_) 
			reserve(cap_ == 0 ? 1 : cap_ * 2) ;
		data_[size_] = utils::move(val) ;
		++size_ ;
	}

	void erase(unsigned idx) {
		if (idx >= size_) 
			throw error_handler::out_of_node_range() ;
        for (unsigned i = idx; i < size_ - 1; ++i) 
			data_[i] = data_[i + 1] ;
        --size_ ;
	}

	void pop() noexcept { 
		if (size_ > 0) 
			--size_ ;
	}

    void shrink_to_fit() {
        if (size_ == cap_ || size_ == 0) 
			return ;
        T* tmp = new T[size_] ;
        for (unsigned i = 0; i < size_; i++) 
			tmp[i] = data_[i] ;
        delete[] data_ ;
        data_ = tmp ;
        cap_ = size_ ;
    }

	bool is_empty() const noexcept {
		return size_ == 0 ;
	}

	void clear() noexcept {
		size_ = 0 ;
	}

	T& get() noexcept { 
		return data_ ; 
	}

	const T& get() const noexcept { 
		return data_ ; 
	}

	T* begin() noexcept { 
		return data_ ; 
	}

	T* end() noexcept { 
		return data_ + size_ ; 
	}

	const T* begin() const noexcept { 
		return data_ ; 
	}

	const T* end() const noexcept { 
		return data_ + size_ ; 
	}
} ;

template <unsigned I, typename ... Ts> struct Tuple_id ;
template <typename T, typename ... Ts> struct Tuple_id<0, T, Ts...> { using Type = T ; } ;
template <unsigned I, typename T, typename ... Ts> struct Tuple_id<I, T, Ts...> : Tuple_id<I - 1, Ts...> {} ;
template <unsigned I, typename... Ts> using Tuple_id_t = typename Tuple_id<I < sizeof...(Ts) ? I : (throw , 0), Ts... >::Type;

template <typename Sequence, typename ... Ts> class Tuple_impl ;

template <unsigned ... Is, typename ... Ts> class Tuple_impl<sequence<Is...>, Ts...> : private Node<Is, Ts>... {
public :
	Tuple_impl() noexcept = default ;
	Tuple_impl(const Ts&... args) noexcept : Node<Is, Ts>(args)... {}
	Tuple_impl(Ts&&... args) noexcept : Node<Is, Ts>(utils::move(args))... {}

	template <unsigned row, unsigned col> decltype(auto) get() noexcept { 
		static_assert(row < sizeof...(Ts), "Index out of range!") ;
		return static_cast<Node<row, Tuple_id_t<row, Ts...>>&>(*this)[col] ; 
	}

	template <unsigned row, unsigned col> decltype(auto) get() const noexcept { 
		static_assert(row < sizeof...(Ts), "Index out of range!") ;
		return static_cast<const Node<row, Tuple_id_t<row, Ts...>>&>(*this)[col] ; 
	}

	template <unsigned col> Tuple_impl& getRow() noexcept { return Tuple_impl{ static_cast<Node<Is, Ts>&>(*this)[col]... } ; }
} ;

}

template <typename ... Ts> using Tuple = impl::Tuple_impl<impl::sequence_for<Ts...>, Ts...> ;

}