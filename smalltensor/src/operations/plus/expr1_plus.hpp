#pragma once


template <typename val_type, std::size_t d1, char i>
ST_ALWAYS_INLINE expr1<val_type,d1,i> operator+(expr1<val_type,d1,i> const&Ri_){
	typedef expr1<val_type,d1,i> ret_type;
	ret_type ret_i;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		ret_i(n1) = + Ri_(n1);
	}
	return ret_i;
}



