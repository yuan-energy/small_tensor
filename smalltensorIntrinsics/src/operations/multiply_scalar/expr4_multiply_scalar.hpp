#pragma once


template <typename val_type, typename scalar_type,
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator*(
       expr4<val_type,d1,d2,d3,d4,i,j,k,l> const& Lijkl_, 
       scalar_type                         const& scalar_
       )
{
	typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
	ret_type ret_ijkl;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			for (std::size_t n3 = 0; n3 < d3; ++n3){
			    for (std::size_t n4 = 0; n4 < d4; ++n4){
					ret_ijkl(n1,n2,n3,n4) = Lijkl_(n1,n2,n3,n4) * scalar_;
				}
			}
		}
	}
	return ret_ijkl;
}

template <typename val_type, typename scalar_type,
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator*(
       scalar_type                         const& scalar_,
       expr4<val_type,d1,d2,d3,d4,i,j,k,l> const& Lijkl_ 
       )
{
	typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
	ret_type ret_ijkl;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			for (std::size_t n3 = 0; n3 < d3; ++n3){
			    for (std::size_t n4 = 0; n4 < d4; ++n4){
					ret_ijkl(n1,n2,n3,n4) = Lijkl_(n1,n2,n3,n4) * scalar_;
				}
			}
		}
	}
	return ret_ijkl;
}
