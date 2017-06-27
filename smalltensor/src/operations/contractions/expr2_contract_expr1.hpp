#ifndef EXPR2_CONTRACT_EXPR1_H_
#define EXPR2_CONTRACT_EXPR1_H_

template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
inline expr1<val_type,d1,i> operator*(
                             expr2<val_type,d1,d2,i,j>const& Lij_, 
                             expr1<val_type,d2,j> const& Rj_) {
    typedef expr1<val_type,d1,i> ret_type;
    ret_type ret_i;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
    	for (std::size_t n2 = 0; n2 < d2; ++n2)
    	{
	        ret_i(N1) += Lij_(N1,n2) * Rj_(n2);
    	}
    }
    return ret_i;
}


template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
inline expr1<val_type,d1,i> operator*(
                             expr2<val_type,d2,d1,j,i>const& Lji_, 
                             expr1<val_type,d2,j> const& Rj_) {
    typedef expr1<val_type,d1,i> ret_type;
    ret_type ret_i;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
    	for (std::size_t n2 = 0; n2 < d2; ++n2)
    	{
	        ret_i(N1) += Lji_(n2,N1) * Rj_(n2);
    	}
    }
    return ret_i;
}



#endif