#pragma once


namespace smalltensor{

template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3,
          char i, char j, char k>
ST_ALWAYS_INLINE expr3<val_type,d1,d2,d3,i,j,k> operator*(
	   expr2<val_type,d1,d2,i,j> const& Lij_, 
	   expr1<val_type,d3,k> const& Rk_){
	typedef expr3<val_type,d1,d2,d3,i,j,k> ret_type;
	ret_type ret_ijk;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			for (std::size_t n3 = 0; n3 < d3; ++n3)
			{
        		ret_ijk(n1,n2,n3) = Lij_(n1,n2) * Rk_(n3) ;
			}
		}
	}
	return ret_ijk;
}




template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3,
          char i, char j, char k>
ST_ALWAYS_INLINE expr3<val_type,d1,d2,d3,i,j,k> operator*(
	   expr1<val_type,d1,i> const& Li_, 
	   expr2<val_type,d2,d3,j,k> const& Rjk_){
	typedef expr3<val_type,d1,d2,d3,i,j,k> ret_type;
	ret_type ret_ijk;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			for (std::size_t n3 = 0; n3 < d3; ++n3)
			{
        		ret_ijk(n1,n2,n3) = Li_(n1) * Rjk_(n2,n3) ;
			}
		}
	}
	return ret_ijk;
}



} // namespace smalltensor{