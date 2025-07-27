#pragma once
#include "zdb_utils.h"

namespace zdb {

namespace error_handler {

struct out_of_MM_range { const char* operator()() const noexcept { return "MM must be range 1 - 12" ; } } ;
struct out_of_DD_range { const char* operator()() const noexcept { return "DD must be range 1 - 31" ; } } ;
struct YY_underflow { const char* operator()() const noexcept { return "YY must be greater then equal 0" ; } } ;
struct out_of_numeric_char_range { const char* operator()() const noexcept { return "character out of range numeric char" ; } } ;
struct invalid_string_len { const char* operator()() const noexcept { return "Invalid text length" ; } } ;

}

namespace utils {

template <typename T, typename Error_Handler> const T& range_control_handler(const T& val, const T& lo, const T& hi, Error_Handler herr) {
	static_assert(impl::is_arithmetic_v<T>, "val, lo, hi must be arithmetics type!") ;
	if(lo > val && hi < val) throw herr() ;
	return val ;
}

template <typename T = uint32> T char2num(char c) {
	if(c >= '0' && c <= '9') return c - '0' ;
	throw error_handler::out_of_numeric_char_range() ;
}

template <typename T> constexpr bool is_leap_year(const T& val) {
	static_assert(impl::is_arithmetic_v<T>, "type must be arithmetic type!") ;
	return (val % 400 == 0) ? true : (val % 100 == 0) ? false : (val % 4 == 0) ? true : false ;
} ;

constexpr uint8 len_day(const uint8& MM, const uint16& YY) noexcept {
	utils::range_control_handler(MM, static_cast<uint8>(1), static_cast<uint8>(12), error_handler::out_of_MM_range{}) ;
	if (MM == 2) { if (is_leap_year(YY)) return 29 ; else return 28 ; }
	constexpr uint8 MM_31[] = {1, 3, 5, 7, 8, 10, 12} ;
	for(auto i = 0; i < 7; ++i) if(MM == MM_31[i]) return 31 ;
	return 30 ;
}

}

namespace impl {

class Date {
private :
	uint8 DD, MM ;
	uint16 YY ;

public :
	Date(uint8 DD, uint8 MM, uint16 YY) noexcept : 
	DD(utils::range_control_handler(DD, static_cast<uint8>(1), utils::len_day(MM, YY), error_handler::out_of_DD_range{})), 
	MM(utils::range_control_handler(MM, static_cast<uint8>(1), static_cast<uint8>(12), error_handler::out_of_MM_range{})), 
	YY(utils::range_control_handler(YY, static_cast<uint16>(0), static_cast<uint16>(~0), error_handler::YY_underflow{})) {}
	
	Date(const varchar<8>& date_str) {
		DD = static_cast<uint8>(utils::char2num(date_str[0]) * 10 + utils::char2num(date_str[1])) ;
		MM = static_cast<uint8>(utils::char2num(date_str[2]) * 10 + utils::char2num(date_str[3])) ;
		YY = static_cast<uint16>(utils::char2num(date_str[4]) * 1000 + utils::char2num(date_str[5]) * 100 + utils::char2num(date_str[6]) * 10 + utils::char2num(date_str[7])) ;
	}

	operator std::string() const noexcept { return std::to_string(DD) + std::to_string(MM) + std::to_string(YY) ; }
	const uint8& getDD() const noexcept { return DD ; }
	const uint8& getMM() const noexcept { return MM ; }
	const uint16& getYY() const noexcept { return YY ; }
	uint8 getDD() noexcept { return DD ; }
	uint8 getMM() noexcept { return MM ; }
	uint16 getYY() noexcept { return YY ; }
	Date& setDD(const uint8& DD) noexcept { this->DD = DD ; return *this ; }
	Date& setMM(const uint8& MM) noexcept { this->MM = MM ; return *this ; }
	Date& setYY(const uint16& YY) noexcept { this->YY = YY ; return *this ; }
} ;

}

}