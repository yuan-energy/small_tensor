#pragma once
#include "../../utils/__utils.h"
#include "../expressions/expressions.h"

using namespace std;
template <typename __dat_t, std::size_t __d1>
class tensor1
{
public:
	__dat_t ST_ALIGN32 _data[__d1] ;

	tensor1(){
		memset(_data, 0, sizeof(__dat_t)*__d1);
	}
	tensor1(tensor1 const& rhs_){
		DEBUG_MSG("tensor1 copy constructor is called");
		std::memcpy(_data, rhs_._data, sizeof(__dat_t)*__d1);
	}
	tensor1& operator=(tensor1 const& rhs_){
		DEBUG_MSG("tensor1 copy assignment operator is called");
		if(this != &rhs_){
	        std::memcpy(_data, rhs_._data, sizeof(__dat_t)*__d1);		
		}
		return *this;
	}
    tensor1(tensor1 && rhs_) noexcept {
    	std::swap(_data, rhs_._data);
    	DEBUG_MSG("tensor1 move constructor is called");

    }
    tensor1& operator=(tensor1&& rhs_) noexcept{
    	DEBUG_MSG("tensor1 move assignment operator is called");
    	if(this != &rhs_){
    		std::swap(_data, rhs_._data);
    	}
    	return *this;
    }
	~tensor1(){
	}

	ST_ALWAYS_INLINE __dat_t& operator()(std::size_t n1_){
		ASSERT_MSG(n1_< __d1 , "tensor1() index out of bounds in lvalue. ");
		return _data[ n1_ ];
	}
	ST_ALWAYS_INLINE __dat_t operator()(std::size_t n1_)const{
		ASSERT_MSG(n1_< __d1 , "tensor1() index out of bounds in rvalue. ");
		return _data[ n1_ ];
	}
	template <char i>
	ST_ALWAYS_INLINE expr1<__dat_t, __d1, i>& operator()(Index<i> i_){
        return static_cast<expr1<__dat_t, __d1, i>&>(*this);
	}
	template <char i>
	ST_ALWAYS_INLINE expr1<__dat_t, __d1, i> const& operator()(Index<i> i_)const{
        return static_cast<expr1<__dat_t, __d1, i>const&>(*this);
	}
	ST_ALWAYS_INLINE tensor1& operator*=(__dat_t const& scalar_){
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			(*this)(n1) *= scalar_ ;
		}
		return (*this);
	}
};


template <typename __dat_t, std::size_t __d1>
std::ostream &operator<<(std::ostream &output, const tensor1<__dat_t, __d1> &v) {
	output << "\n" ; 
	for (size_t i = 0; i < __d1; ++i) {
		output << v(i) << " " ; 
	}
  	return output;
}

