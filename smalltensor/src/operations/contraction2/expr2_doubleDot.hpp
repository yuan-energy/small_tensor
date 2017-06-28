#ifndef EXPR2_DOUBLE_DOT_HPP_
#define EXPR2_DOUBLE_DOT_HPP_

template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
inline val_type operator* (expr2<val_type,d1,d2,i,j> const& Lij_,  
                           expr2<val_type,d1,d2,i,j> const& Rij_){
    val_type ret{0};
    for (std::size_t n1 = 0; n1 < d1; ++n1){
        for (std::size_t n2 = 0; n2 < d2; ++n2){
            ret += Lij_(n1,n2) * Rij_(n1,n2);
        }
    }
    return ret;
}



template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
inline expr2<val_type,d1,d2,i,j> operator*(
                                  expr4<val_type,d1,d2,d3,d4,i,j,k,l>const& Lijkl_, 
                                  expr2<val_type,d3,d4,k,l> const& Rkl_) {
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
        for (std::size_t N2 = 0; N2 < d2; ++N2){
            for (std::size_t n3 = 0; n3 < d3; ++n3){
                for (std::size_t n4 = 0; n4 < d4; ++n4)
                {
                    ret_ij(N1,N2,n3,n4) += Lijkl_(N1,N2,n3,n4) * Rkl_(n3,n4);
                }
            }
        }
    }
    return ret_ij;
}


#endif