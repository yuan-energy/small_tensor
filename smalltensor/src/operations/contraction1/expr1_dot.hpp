#pragma once

namespace smalltensor{

template <typename val_type, std::size_t d1, char i>
ST_ALWAYS_INLINE val_type operator*(
       expr1<val_type,d1,i> const& Li_, 
       expr1<val_type,d1,i> const& Ri_) {
    val_type ret{0};
    for (std::size_t n1 = 0; n1 < d1; ++n1){
        ret += Li_(n1) * Ri_(n1);
    }
    return ret;
}


template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
ST_ALWAYS_INLINE expr1<val_type,d1,i> operator*(
       expr2<val_type,d1,d2,i,j> const& Lij_, 
       expr1<val_type,d2,j>      const& Rj_) {
    typedef expr1<val_type,d1,i> ret_type;
    ret_type ret_i;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      ret_i(N1)=0;
    	for (std::size_t n2 = 0; n2 < d2; ++n2)
    	{
	        ret_i(N1) += Lij_(N1,n2) * Rj_(n2);
    	}
    }
    return ret_i;
}


template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
ST_ALWAYS_INLINE expr1<val_type,d1,i> operator*(
       expr1<val_type,d2,j>      const& Lj_, 
       expr2<val_type,d1,d2,i,j> const& Rij_) {
    typedef expr1<val_type,d1,i> ret_type;
    ret_type ret_i;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      ret_i(N1)=0;
    	for (std::size_t n2 = 0; n2 < d2; ++n2)
    	{
	        ret_i(N1) += Lj_(n2) * Rij_(N1,n2);
    	}
    }
    return ret_i;
}

} // namespace smalltensor


