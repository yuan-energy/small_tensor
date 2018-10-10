#pragma once

template <typename val_type, std::size_t d1, std::size_t d2, char i1, char i2>
ST_ALWAYS_INLINE expr2<val_type,d1,d2,i1,i2> operator+(
       expr2<val_type,d1,d2,i1,i2> const& Rij_){
	typedef expr2<val_type,d1,d2,i1,i2> ret_type;
	ret_type ret_ij;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			ret_ij(n1,n2) = + Rij_(n1,n2);
		}
	}
	return ret_ij;
}




