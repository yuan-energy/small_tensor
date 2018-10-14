#pragma once

namespace smalltensor{

template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          std::size_t d5, 
          char i, char j, char k, char l, char m>
ST_ALWAYS_INLINE expr3<val_type,d1,d2,d3,i,j,k> operator*(
       expr4<val_type,d1,d2,d4,d5,i,j,l,m> const& Lijlm_, 
       expr3<val_type,d4,d5,d3,l,m,k>      const& Rlmk_) {
    typedef expr3<val_type,d1,d2,d3,i,j,k> ret_type;
    ret_type ret_ijk;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          ret_ijk(N1,N2,N3)=0;
          for (std::size_t n4 = 0; n4 < d4; ++n4){
            for (std::size_t n5 = 0; n5 < d5; ++n5){
              ret_ijk(N1,N2,N3) += Lijlm_(N1,N2,n4,n5) * Rlmk_(n4,n5,N3);
            }
          }
        }
      }
    }
    return ret_ijk;
}



template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          std::size_t d5, 
          char i, char j, char k, char l, char m>
ST_ALWAYS_INLINE expr3<val_type,d1,d2,d3,i,j,k> operator*(
       expr3<val_type,d1,d4,d5,i,l,m> const& Lilm_, 
       expr4<val_type,d4,d5,d2,d3,l,m,j,k>  const& Rlmjk_) {
    typedef expr3<val_type,d1,d2,d3,i,j,k> ret_type;
    ret_type ret_ijk;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          ret_ijk(N1,N2,N3)=0;
          for (std::size_t n4 = 0; n4 < d4; ++n4){
            for (std::size_t n5 = 0; n5 < d5; ++n5){
              ret_ijk(N1,N2,N3) += Lilm_(N1,n4,n5) * Rlmjk_(n4,n5,N2,N3);
            }
          }
        }
      }
    }
    return ret_ijk;
}


} // namespace smalltensor

