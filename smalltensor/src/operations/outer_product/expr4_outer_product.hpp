#pragma once


namespace smalltensor{

template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator*(
	   expr3<val_type,d1,d2,d3,i,j,k> const& Lijk_, 
	   expr1<val_type,d4,l> const& Rl_){
	typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
	ret_type ret_ijkl;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			for (std::size_t n3 = 0; n3 < d3; ++n3){
				for (std::size_t n4 = 0; n4 < d4; ++n4)
		        {
    		        ret_ijkl(n1,n2,n3,n4) = Lijk_(n1,n2,n3) * Rl_(n4) ;
    		    }
			}
		}
	}
	return ret_ijkl;
}



template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator*(
	   expr1<val_type,d1,i> const& Li_, 
	   expr3<val_type,d2,d3,d4,j,k,l> const& Rjkl_){
	typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
	ret_type ret_ijkl;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			for (std::size_t n3 = 0; n3 < d3; ++n3){
				for (std::size_t n4 = 0; n4 < d4; ++n4)
		        {
    		        ret_ijkl(n1,n2,n3,n4) = Li_(n1) * Rjkl_(n2,n3,n4) ;
    		    }
			}
		}
	}
	return ret_ijkl;
}



template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator*(
	   expr2<val_type,d1,d2,i,j> const& Lij_, 
	   expr2<val_type,d3,d4,k,l> const& Rkl_){
	typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
	ret_type ret_ijkl;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			for (std::size_t n3 = 0; n3 < d3; ++n3){
				for (std::size_t n4 = 0; n4 < d4; ++n4)
		        {
    		        ret_ijkl(n1,n2,n3,n4) = Lij_(n1,n2) * Rkl_(n3,n4) ;
    		    }
			}
		}
	}
	return ret_ijkl;
}

} // namespace smalltensor{