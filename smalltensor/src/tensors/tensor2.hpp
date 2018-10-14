#pragma once
#include "../../utils/__utils.h"
#include "../expressions/expressions.h"

using namespace std;

namespace smalltensor{

template <typename __dat_t, std::size_t __d1, std::size_t __d2>
class tensor2
{
public:
	
	__dat_t ST_ALIGN32 _data[__d1*__d2] ;

	tensor2(){
		memset(_data, 0, sizeof(__dat_t)*__d1*__d2) ; 
	}
	tensor2(tensor2 const& rhs_){
		DEBUG_MSG("tensor2 copy constructor is called");
		std::memcpy(_data, rhs_._data, sizeof(__dat_t)*__d1*__d2);
	}
	tensor2& operator=(tensor2 const& rhs_){
		DEBUG_MSG("tensor2 copy assignment operator is called");
		if(this != &rhs_){
	        std::memcpy(_data, rhs_._data, sizeof(__dat_t)*__d1*__d2);		
		}
		return *this;
	}

    tensor2(tensor2&& rhs_) noexcept
    {
    	std::swap(_data, rhs_._data);
    	DEBUG_MSG("tensor2 move constructor is called");
    }
    tensor2& operator=(tensor2&& rhs_) noexcept{
    	if(this != &rhs_){
    		std::swap(_data, rhs_._data);
    	}
    	DEBUG_MSG("tensor2 move assignment operator is called");
    	return *this;
    }
	~tensor2(){
	}
	tensor2(std::string const& other_){
		memset(_data, 0, sizeof(__dat_t)*__d1*__d2) ; 
	    if (other_ == "identity")
	    {
	        ASSERT_MSG(__d1==__d2, "ERROR:tensor2 has different dimensions, cannot be identity.");
	        for (std::size_t n1 = 0; n1 < __d1; ++n1)
	        {
	            (*this)(n1,n1) = 1;
	        }
	    }
	}
	ST_ALWAYS_INLINE __dat_t& operator()(std::size_t n1_, std::size_t n2_){
		ASSERT_MSG(n1_< __d1 && n2_ < __d2, "tensor2() index out of bounds in lvalue. ");
		return _data[ n1_ * __d2 + n2_];
	}
	ST_ALWAYS_INLINE __dat_t operator()(std::size_t n1_, std::size_t n2_)const{
		ASSERT_MSG(n1_< __d1 && n2_ < __d2, "tensor2() index out of bounds in rvalue. ");
		return _data[ n1_ * __d2 + n2_];
	}
	template <char i, char j>
	ST_ALWAYS_INLINE expr2<__dat_t, __d1, __d2, i, j>& operator()(Index<i> i_, Index<j> j_){
        return static_cast<expr2<__dat_t, __d1, __d2, i, j>&>(*this);
	}

	template <char i, char j>
	ST_ALWAYS_INLINE expr2<__dat_t, __d1, __d2, i, j> const& operator()(Index<i> i_, Index<j> j_)const{
        return static_cast<expr2<__dat_t, __d1, __d2, i, j>const&>(*this);
	}

	template <char i>
	ST_ALWAYS_INLINE __dat_t operator()(Index<i> i_, Index<i/*same*/> j_){
		ASSERT_MSG(__d1 == __d2, "Dimension size should be equal for dummy indices. ");
		__dat_t ret=0;
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			ret += (*this)(n1,n1);
		}
        return ret;
	}

	ST_ALWAYS_INLINE tensor2& operator*=(__dat_t const& scalar_){
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			for (std::size_t n2 = 0; n2 < __d2; ++n2){
				(*this)(n1,n2) *= scalar_ ;
			}
		}
		return (*this);
	}

	

};

template <typename __dat_t, std::size_t __d1, std::size_t __d2>
std::ostream &operator<<(std::ostream &output, const tensor2<__dat_t, __d1,__d2> &v) {
	output << "\n" ; 
	for (size_t i = 0; i < __d1; ++i) {
		for (size_t j = 0; j < __d2; ++j) {
  			output << v(i,j) << " " ; 
		}
		output << "\n" ; 
	}
  return output;
}

} // smalltensor
