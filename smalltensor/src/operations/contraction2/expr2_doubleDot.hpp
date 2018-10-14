#pragma once

namespace smalltensor{

template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr2<val_type,d1,d2,i,j> operator*(
       expr4<val_type,d1,d2,d3,d4,i,j,k,l> const& Lijkl_, 
       expr2<val_type,d3,d4,k,l>           const& Rkl_) {
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        ret_ij(N1,N2)=0;
        for (std::size_t n3 = 0; n3 < d3; ++n3){
          for (std::size_t n4 = 0; n4 < d4; ++n4){
            ret_ij(N1,N2) += Lijkl_(N1,N2,n3,n4) * Rkl_(n3,n4);
          }
        }
      }
    }
    return ret_ij;
}


template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr2<val_type,d1,d2,i,j> operator*(
       expr3<val_type,d1,d3,d4,i,k,l> const& Likl_, 
       expr3<val_type,d3,d4,d2,k,l,j> const& Rklj_) {
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        ret_ij(N1,N2)=0;
        for (std::size_t n3 = 0; n3 < d3; ++n3){
          for (std::size_t n4 = 0; n4 < d4; ++n4)
          {
            ret_ij(N1,N2) += Likl_(N1,n3,n4) * Rklj_(n3,n4,N2);
          }
        }
      }
    }
    return ret_ij;
}


template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr2<val_type,d1,d2,i,j> operator*(
       expr2<val_type,d3,d4,k,l>           const& Lkl_, 
       expr4<val_type,d3,d4,d1,d2,k,l,i,j> const& Rklij_) {
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        ret_ij(N1,N2)=0;
        for (std::size_t n3 = 0; n3 < d3; ++n3){
          for (std::size_t n4 = 0; n4 < d4; ++n4)
          {
            ret_ij(N1,N2) += Lkl_(n3,n4) * Rklij_(n3,n4,N1,N2);
          }
        }
      }
    }
    return ret_ij;
}

}
