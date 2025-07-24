#pragma once
#include <vector>
#include <initializer_list>
#include "zdb_type_date.hpp"

namespace zdb {

namespace rule {

enum table : zdb::uint8 {
	AUTO_INCREAMENT,
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
			delete static_cast<utils::getTypeByFlag_v<typefg>*>(data) ;
	}

	Column& add(const T& data) noexcept {
		datas.push_back(new T(data)) ;
		return *this ;
	}

	Column& add(const std::initializer_list<T>& datas) noexcept {
		for(const auto& data : datas)
			this->datas.push_back(new T(data)) ;
		return *this ;
	}

	Column& erase(const uint128& idx) noexcept {
		delete static_cast<T*>(datas[idx]) ;
		datas.erase(datas.begin() + idx) ;
		return *this ;
	}

	Column& clear() noexcept {
		for(void* data : datas)
			delete static_cast<T*>(data) ;
		datas.clear() ;
		return *this ;
	}

	bool is_exist(const T& val) const noexcept {
		return find(val) != static_cast<uint128>(-1) ;
	}

	uint128 size() const noexcept {
		return datas.size() ;
	}

	const T& operator[](uint128 idx) const noexcept {
		return *static_cast<T*>(datas[idx]) ;
	}

	T& operator[](uint128 idx) noexcept {
		return *static_cast<T*>(datas[idx]) ;
	}

	uint128 find(const T& val) const noexcept {
		for(auto i = 0; i < datas.size(); i++)
			if(val == *static_cast<T*>(datas[i]))
				return i ;
		return static_cast<uint128>(-1) ;
	}
} ;

}