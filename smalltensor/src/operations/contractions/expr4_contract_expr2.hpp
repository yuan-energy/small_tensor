#ifndef EXPR4_CONTRACT_EXPR2_H_
#define EXPR4_CONTRACT_EXPR2_H_

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



template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          std::size_t d5,
          char i, char j, char k, char l, char m>
inline expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator*(
                                            expr4<val_type,d1,d2,d3,d5,i,j,k,m>const& Lijkm_, 
                                            expr2<val_type,d5,d4,m,l> const& Rml_) {
    typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
    ret_type ret_ijkl;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
        for (std::size_t N2 = 0; N2 < d2; ++N2){
            for (std::size_t N3 = 0; N3 < d3; ++N3){
                for (std::size_t N4 = 0; N4 < d4; ++N4){
                    for (std::size_t n5 = 0; n5 < d5; ++n5)
                    {
                        ret_ijkl(N1,N2,N3,N4) += Lijkm_(N1,N2,N3,n5) * Rml_(n5,N4);
                    }
                }
            }
        }
    }
    return ret_ijkl;
}


#endif