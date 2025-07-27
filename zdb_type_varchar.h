#pragma once
#include <cstring>

namespace zdb {

namespace error_handler {

struct out_of_constant_char_range { const char* operator()() const noexcept { return "constant char index out of range!" ; } }  ;

}

namespace impl {

template <unsigned I>  class constant_char {
private:
	char text[I + 1]{} ; 

	unsigned strlen_(const char* s) const noexcept {
		unsigned i = 0 ;
		while (s[i] != '\0') ++i ;
		return i ;
	}

public:
	constant_char() noexcept = default ;
	constant_char(const char* str) noexcept { assign(str) ; }
	constant_char(const constant_char& o) noexcept { assign(o.text) ; }
	constant_char(constant_char&& o) noexcept { assign(o.text) ; }
	constant_char& operator=(const char* str) noexcept { assign(str) ; return *this ; }
	constant_char& operator=(const constant_char& o) noexcept { if (this != &o) assign(o.text) ; return *this ; }
	constant_char& operator=(constant_char&& o) noexcept { if (this != &o) assign(o.text) ; return *this ; }
	char& operator[](unsigned idx) noexcept { if (idx >= I) throw error_handler::out_of_constant_char_range{} ; return text[idx] ; }
	const char& operator[](unsigned idx) const noexcept { if (idx >= I) throw error_handler::out_of_constant_char_range{} ; return text[idx] ; }
	operator const char*() const noexcept { return text ; }
	bool operator==(const char* str) const noexcept { return std::strncmp(text, str, I) == 0 ; }
	bool operator!=(const char* str) const noexcept { return !(*this == str) ; }

	unsigned len() const noexcept {
		unsigned i = 0 ;
		while (i < I && text[i] != '\0') ++i ;
		return i ;
	}

	constant_char& assign(const char* str) noexcept {
		unsigned i = 0 ;
		while (i < I && str[i] != '\0') {
			text[i] = str[i] ;
			++i ;
		}
		text[i] = '\0' ;
		return *this ;
	}
} ;

}

}