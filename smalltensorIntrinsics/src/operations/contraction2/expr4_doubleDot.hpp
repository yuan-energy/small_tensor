#pragma once



template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          std::size_t d5, std::size_t d6,
          char i, char j, char k, char l, char m, char n>
ST_ALWAYS_INLINE expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator*(
       expr4<val_type,d1,d2,d5,d6,i,j,m,n> const& Lijmn_, 
       expr4<val_type,d5,d6,d3,d4,m,n,k,l> const& Rmnkl_) {
    typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
    ret_type ret_ijkl;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          for (std::size_t N4 = 0; N4 < d4; ++N4){
            ret_ijkl(N1,N2,N3,N4)=0;
            for (std::size_t n5 = 0; n5 < d5; ++n5){
              for (std::size_t n6 = 0; n6 < d6; ++n6){
                ret_ijkl(N1,N2,N3,N4) += Lijmn_(N1,N2,n5,n6) * Rmnkl_(n5,n6,N3,N4);
              }
            }
          }
        }
      }
    }
    return ret_ijkl;
}



