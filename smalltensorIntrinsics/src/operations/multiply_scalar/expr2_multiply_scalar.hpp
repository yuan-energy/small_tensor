#pragma once

template <typename val_type, typename scalar_type, std::size_t d1, std::size_t d2, char i, char j>
ST_ALWAYS_INLINE expr2<val_type,d1,d2,i,j> operator*(
       expr2<val_type,d1,d2,i,j> const& Lij_, 
       scalar_type               const& scalar_
       )
{
	typedef expr2<val_type,d1,d2,i,j> ret_type;
	ret_type ret_ij;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			ret_ij(n1,n2) = Lij_(n1,n2) * scalar_;
		}
	}
	return ret_ij;
}

template <typename val_type, typename scalar_type, std::size_t d1, std::size_t d2, char i, char j>
ST_ALWAYS_INLINE expr2<val_type,d1,d2,i,j> operator*(
       scalar_type               const& scalar_,
       expr2<val_type,d1,d2,i,j> const& Lij_
       )
{
	typedef expr2<val_type,d1,d2,i,j> ret_type;
	ret_type ret_ij;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			ret_ij(n1,n2) = Lij_(n1,n2) * scalar_;
		}
	}
	return ret_ij;
}

