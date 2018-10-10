#pragma once
#include "../../utils/__utils.h"
#include "../expressions/expressions.h"

using namespace std;
template <typename __dat_t, std::size_t __d1, std::size_t __d2, std::size_t __d3, std::size_t __d4>
class tensor4
{
public:
	__dat_t ST_ALIGN32 _data[__d1*__d2*__d3*__d4] ;

	tensor4(){
		memset(_data, 0, sizeof(__dat_t)*__d1*__d2*__d3*__d4) ; 
	}
	tensor4(tensor4 const& rhs_){
		DEBUG_MSG("tensor4 copy constructor is called");
		std::memcpy(_data, rhs_._data, sizeof(__dat_t)*__d1*__d2*__d3*__d4);
	}
	tensor4& operator=(tensor4 const& rhs_){
		DEBUG_MSG("tensor4 copy assignment operator is called");
		if(this != &rhs_){
	        std::memcpy(_data, rhs_._data, sizeof(__dat_t)*__d1*__d2*__d3*__d4);		
		}
		return *this;
	}
    tensor4(tensor4&& rhs_) noexcept {
    	std::swap(_data, rhs_._data);
    	DEBUG_MSG("tensor4 move constructor is called");

    }
    tensor4& operator=(tensor4&& rhs_) noexcept{
    	DEBUG_MSG("tensor4 move assignment operator is called");
    	if(this != &rhs_){
    		std::swap(_data, rhs_._data);
    	}
    	return *this;
    }
	~tensor4(){
	}

	ST_ALWAYS_INLINE __dat_t& operator()(std::size_t n1_, std::size_t n2_,  
							   std::size_t n3_, std::size_t n4_){
		ASSERT_MSG(n1_< __d1 && n2_ < __d2 && n3_< __d3 && n4_ < __d4,
			"tensor4() index out of bounds in lvalue. ");
		return _data[ n1_ * __d2 * __d3 *__d4 + n2_ * __d3 * __d4 + n3_ * __d4 + n4_];
	}
	ST_ALWAYS_INLINE __dat_t operator()(std::size_t n1_, std::size_t n2_, 
		                      std::size_t n3_, std::size_t n4_)const{
		ASSERT_MSG(n1_< __d1 && n2_ < __d2 && n3_< __d3 && n4_ < __d4, 
			"tensor4() index out of bounds in rvalue. ");
		return _data[ n1_ * __d2 * __d3 *__d4 + n2_ * __d3 * __d4 + n3_ * __d4 + n4_];
	}
	template <char i, char j, char k, char l>
	ST_ALWAYS_INLINE expr4<__dat_t, __d1, __d2, __d3, __d4, i, j, k, l>& 
	operator()(Index<i> i_, Index<j> j_, Index<k> k_, Index<l> l_){
        return static_cast<expr4<__dat_t, __d1, __d2, __d3, __d4, i, j, k, l>&>(*this);
	}
	template <char i, char j, char k, char l>
	ST_ALWAYS_INLINE expr4<__dat_t, __d1, __d2, __d3, __d4, i, j, k, l> const& 
	operator()(Index<i> i_, Index<j> j_, Index<k> k_, Index<l> l_)const{
        return static_cast<expr4<__dat_t, __d1, __d2, __d3, __d4, i, j, k, l>const&>(*this);
	}
	template <char i, char j, char k>
	ST_ALWAYS_INLINE expr2<__dat_t, __d1, __d2, i, j> 
	operator()(Index<i> i_, Index<j> j_, Index<k> k_, Index<k/*same*/> l_){
		ASSERT_MSG(__d3 == __d4, "Dimension size should be equal for dummy indices. ");
		typedef expr2<__dat_t, __d1, __d2, i, j> ret_type;
		ret_type ret_ij;
		for (std::size_t N1 = 0; N1 < __d1; ++N1){
			for (std::size_t N2 = 0; N2 < __d2; ++N2){
				for (std::size_t n3 = 0; n3 < __d3; ++n3){
					ret_ij(N1,N2) += (*this)(N1,N2,n3,n3);
				}
			}
		}
        return ret_ij;
	}

	ST_ALWAYS_INLINE tensor4& operator*=(__dat_t const& scalar_){
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			for (std::size_t n2 = 0; n2 < __d2; ++n2){
				for (std::size_t n3 = 0; n3 < __d3; ++n3){
					for (std::size_t n4 = 0; n4 < __d4; ++n4){
						(*this)(n1,n2,n3,n4) *= scalar_ ;
					}
				}
			}
		}
		return (*this);
	}
};

