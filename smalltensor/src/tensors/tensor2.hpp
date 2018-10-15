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
		ASSERT_MSG(n1_< __d1 && n2_ < __d2, "tensor2() eindex out of bounds in lvalue. ");
		return _data[ n1_ * __d2 + n2_];
	}
	ST_ALWAYS_INLINE __dat_t operator()(std::size_t n1_, std::size_t n2_)const{
		ASSERT_MSG(n1_< __d1 && n2_ < __d2, "tensor2() eindex out of bounds in rvalue. ");
		return _data[ n1_ * __d2 + n2_];
	}
	template <char i, char j>
	ST_ALWAYS_INLINE expr2<__dat_t, __d1, __d2, i, j>& operator()(eindex<i> i_, eindex<j> j_){
        return static_cast<expr2<__dat_t, __d1, __d2, i, j>&>(*this);
	}

	template <char i, char j>
	ST_ALWAYS_INLINE expr2<__dat_t, __d1, __d2, i, j> const& operator()(eindex<i> i_, eindex<j> j_)const{
        return static_cast<expr2<__dat_t, __d1, __d2, i, j>const&>(*this);
	}

	template <char i>
	ST_ALWAYS_INLINE __dat_t operator()(eindex<i> i_, eindex<i/*same*/> j_){
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

	ST_ALWAYS_INLINE const tensor2 Inv() const
	{
	    assert( 3 == __d1 );
	    assert( 3 == __d2 );

	    const __dat_t det = compute_Determinant();
	    tensor2 inverse ; 
	    if (det != 0 ){
	    	const float invDet = 1.0f / det;
	    	__dat_t col0[3] = {_data[0], _data[3], _data[6]} ;
	    	__dat_t col1[3] = {_data[1], _data[4], _data[7]} ;
	    	__dat_t col2[3] = {_data[2], _data[5], _data[8]} ;

	    	inverse._data[0] = invDet * (col1[1]  * col2[2] - col2[1] * col1[2]);
	    	inverse._data[3] = invDet * -(col0[1] * col2[2] - col2[1] * col0[2]);
	    	inverse._data[6] = invDet * (col0[1] * col1[2] - col0[2] * col1[1] );

	    	inverse._data[1] = invDet * -(col1[0] * col2[2] - col1[2] * col2[0]);
	    	inverse._data[4] = invDet * (col0[0] * col2[2] - col0[2] * col2[0]);
	    	inverse._data[7] = invDet * -(col0[0] * col1[2] - col0[2] * col1[0]);

	    	inverse._data[2] = invDet * (col1[0] * col2[1] - col1[1]  * col2[0]);
	    	inverse._data[5] = invDet * -(col0[0] * col2[1] - col0[1] * col2[0]);
	    	inverse._data[8] = invDet * (col0[0] * col1[1]  - col1[0] * col0[1]);
	    	return inverse ; 
	    }else{
	    	inverse._data[0] = 1 ;
	    	inverse._data[3] = 1 ;
	    	inverse._data[6] = 1 ;
	    	return inverse ; 
	    }

	}

	__dat_t ST_ALWAYS_INLINE compute_Determinant( )	const {
		assert( 3 == __d1 );
		assert( 3 == __d2 );

		__dat_t col0[3] = {_data[0], _data[3], _data[6]} ;
		__dat_t col1[3] = {_data[1], _data[4], _data[7]} ;
		__dat_t col2[3] = {_data[2], _data[5], _data[8]} ;
		__dat_t cross[3] = {col1[1] * col2[2] - col1[2] * col2[1] ,
							col1[2] * col2[0] - col1[0] * col2[2] , 
							col1[0] * col2[1] - col1[1] * col2[0]
				} ; 
		return col0[0] * cross[0] + col0[1] * cross[1] + col0[2] * cross[2] ; // dot product
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
