#ifndef TENSOR2_HPP_
#define TENSOR2_HPP_
#include "../utils/__utils.h"
#include "../expressions/expr2/expr2s.h"
#include "../expressions/index.hpp"

using namespace std;
template <typename __dat_t, std::size_t __d1, std::size_t __d2>
class tensor2
{
public:
	__dat_t* __restrict__ _data;

	tensor2(): _data{new __dat_t[__d1*__d2]}{}
	tensor2(tensor2 const& rhs_): _data{new __dat_t[__d1*__d2]}{
		std::memcpy(_data, rhs_._data, sizeof(_data));
	}
	tensor2& operator=(tensor2 const& rhs_){
		if(this != &rhs_){
	        std::memcpy(_data, rhs_._data, sizeof(_data));		
		}
		return *this;
	}
    tensor2(tensor2&& rhs_) noexcept: _data{std::move(rhs_._data)}{}
    tensor2& operator=(tensor2&& rhs_) noexcept{
    	if(this != &rhs_){
    		_data = std::move(rhs_._data);
    	}
    	return *this;
    }
	~tensor2(){
		if (_data!=nullptr){
		    delete[] _data;
		    _data=nullptr;
		}
	}

	inline __dat_t& operator()(std::size_t n1_, std::size_t n2_){
		ASSERT_MSG(n1_< __d1 && n2_ < __d2, "tensor2() index out of bounds in lvalue. ");
		return _data[ n1_ * __d2 + n2_];
	}
	inline __dat_t operator()(std::size_t n1_, std::size_t n2_)const{
		ASSERT_MSG(n1_< __d1 && n2_ < __d2, "tensor2() index out of bounds in rvalue. ");
		return _data[ n1_ * __d2 + n2_];
	}
	template <char i, char j>
	inline expr2<__dat_t, __d1, __d2, i, j>& operator()(Index<i> i_, Index<j> j_){
        return static_cast<expr2<__dat_t, __d1, __d2, i, j>&>(*this);
	}
};

#endif