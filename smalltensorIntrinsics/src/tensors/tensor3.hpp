#pragma once
#include "../../utils/__utils.h"
#include "../expressions/expressions.h"

using namespace std;
template <typename __dat_t, std::size_t __d1, std::size_t __d2, std::size_t __d3>
class tensor3
{
public:
	__dat_t ST_ALIGN32 _data[__d1*__d2*__d3] ;

	tensor3(){
		memset(_data, 0, sizeof(__dat_t)*__d1*__d2*__d3) ; 
	}
	tensor3(tensor3 const& rhs_){
		DEBUG_MSG("tensor3 copy constructor is called");
		std::memcpy(_data, rhs_._data, sizeof(__dat_t)*__d1*__d2*__d3);
	}
	tensor3& operator=(tensor3 const& rhs_){
		DEBUG_MSG("tensor3 copy assignment operator is called");
		if(this != &rhs_){
	        std::memcpy(_data, rhs_._data, sizeof(__dat_t)*__d1*__d2*__d3);		
		}
		return *this;
	}
    tensor3(tensor3&& rhs_) noexcept
    {
    	std::swap(_data, rhs_._data);
    	DEBUG_MSG("tensor3 move constructor is called");
    }
    tensor3& operator=(tensor3&& rhs_) noexcept{
    	DEBUG_MSG("tensor3 move assignment operator is called");
    	if(this != &rhs_){
    		std::swap(_data, rhs_._data);
    	}
    	return *this;
    }
	~tensor3(){
	}

	ST_ALWAYS_INLINE __dat_t& operator()(std::size_t n1_, std::size_t n2_, std::size_t n3_){
		ASSERT_MSG(n1_< __d1 && n2_ < __d2 && n3_ < __d3, "tensor3() index out of bounds in lvalue. ");
		return _data[ n1_ * __d2 *__d3 + n2_ * __d3 + n3_];
	}
	ST_ALWAYS_INLINE __dat_t operator()(std::size_t n1_, std::size_t n2_, std::size_t n3_)const{
		ASSERT_MSG(n1_< __d1 && n2_ < __d2 && n3_ < __d3, "tensor3() index out of bounds in rvalue. ");
		return _data[ n1_ * __d2 *__d3 + n2_ * __d3 + n3_];
	}
	template <char i, char j, char k>
	ST_ALWAYS_INLINE expr3<__dat_t, __d1, __d2, __d3, i, j, k>& operator()(Index<i> i_, Index<j> j_, Index<k> k_){
        return static_cast<expr3<__dat_t, __d1, __d2, __d3, i, j, k>&>(*this);
	}
	template <char i, char j, char k>
	ST_ALWAYS_INLINE expr3<__dat_t, __d1, __d2, __d3, i, j, k> const& operator()(Index<i> i_, Index<j> j_, Index<k> k_)const{
        return static_cast<expr3<__dat_t, __d1, __d2, __d3, i, j, k>const&>(*this);
	}
	template <char i, char j>
	ST_ALWAYS_INLINE expr1<__dat_t, __d1, i> operator()(Index<i> i_, Index<j> j_, Index<j> k_){
		ASSERT_MSG(__d2 == __d3, "Dimension size should be equal for dummy indices. ");
		typedef expr1<__dat_t, __d1, i> ret_type;
		ret_type ret_i;
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			for (std::size_t n2 = 0; n2 < __d2; ++n2)
			{
				ret_i(n1) += (*this)(n1,n2,n2);
			}
		}
        return ret_i;
	}
	ST_ALWAYS_INLINE tensor3& operator*=(__dat_t const& scalar_){
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			for (std::size_t n2 = 0; n2 < __d2; ++n2){
				for (std::size_t n3 = 0; n3 < __d3; ++n3){
					(*this)(n1,n2,n3) *= scalar_ ;
				}
			}
		}
		return (*this);
	}
};

