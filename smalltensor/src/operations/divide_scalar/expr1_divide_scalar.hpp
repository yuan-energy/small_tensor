#pragma once

namespace smalltensor{
	

template <typename val_type, typename scalar_type, std::size_t d1, char i>
ST_ALWAYS_INLINE expr1<val_type,d1,i> operator/(
       expr1<val_type,d1,i> const& Li_, 
       scalar_type          const& scalar_){
	typedef expr1<val_type,d1,i> ret_type;
	ret_type ret_i;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		ret_i(n1) = Li_(n1) / scalar_;
	}
	return ret_i;
}






}
