#pragma once
#include <vector>
#include <initializer_list>
#include "zdb_type_date.hpp"

namespace zdb {

namespace rule {

enum table : zdb::uint8 {
	AUTO_INCREMENT,
	FOREIGN_KEY,
	UNIQUE,
	GRANT_NULL
} ;

}

class Column {
private :
	typesFg fg ;
	std::string header ;
	std::vector<void*> datas ;

public :
	Column(const std::string& header, typesFg fg) noexcept : header(header), fg(fg) {}
	~Column() noexcept {
		for(void* data : datas)
			type
	}

	Column& add(const void* data) noexcept {
		utils::OpBySpecType(fg, [&](auto tw){
			using U = typename decltype(tw)::type ;
			datas.push_back(new U(*static_cast<const U*>(data))) ;
		}) ;
		return *this ;
	}

	Column& add(const std::initializer_list<void*>& datas) noexcept {
		for(const auto& data : datas)
			utils::OpBySpecType(fg, [&](auto tw){
				using U = typename decltype(tw)::type ;
				this->datas.push_back(new U(*static_cast<const U*>(data))) ;
			}) ;
			
		return *this ;
	}

	Column& erase(const uint128& idx) noexcept {
		utils::OpBySpecType(fg, [&](auto tw){
			using U = typename decltype(tw)::type ;
			delete static_cast<U*>(datas[idx]) ;
		}) ;
		datas.erase(datas.begin() + idx) ;
		return *this ;
	}

	Column& clear() noexcept {
		for(void* data : datas)
			utils::OpBySpecType(fg, [&](auto tw){
				using U = typename decltype(tw)::type ;
				delete static_cast<U*>(data) ;
			}) ;
		datas.clear() ;
		return *this ;
	}

	bool is_exist(const void* val) const noexcept {
		return find(val) != static_cast<uint128>(-1) ;
	}

	uint128 size() const noexcept {
		return datas.size() ;
	}

	const void* operator[](uint128 idx) const noexcept {
		return datas[idx] ;
	}

	void* operator[](uint128 idx) noexcept {
		return datas[idx] ;
	}

	uint128 find(const void* val) const noexcept {
		bool match = false ;
		for(auto i = 0; i < datas.size(); i++) {
			utils::OpBySpecType(fg, [&](auto tw) -> bool {
				using U = typename decltype(tw)::type ;
				match = (*static_cast<U*>(datas[i]) == *static_cast<const U*>(val)) ;
			}) ;
			if (match)
				return i ;
		}
		return static_cast<uint128>(-1) ;
	}
} ;

}