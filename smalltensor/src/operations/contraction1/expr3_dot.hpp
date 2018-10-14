#pragma once

namespace smalltensor{

template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr3<val_type,d1,d2,d3,i,j,k> operator*(
       expr4<val_type,d1,d2,d3,d4,i,j,k,l> const& Lijkl_, 
       expr1<val_type,d4,l>                const& Rl_) {
    typedef expr3<val_type,d1,d2,d3,i,j,k> ret_type;
    ret_type ret_ijk;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          ret_ijk(N1,N2,N3)=0;
          for (std::size_t n4 = 0; n4 < d4; ++n4){
            ret_ijk(N1,N2,N3) += Lijkl_(N1,N2,N3,n4) * Rl_(n4);
          }
        }
      }
    }
    return ret_ijk;
}


template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr3<val_type,d1,d2,d3,i,j,k> operator*(
       expr3<val_type,d1,d2,d4,i,j,l> const& Lijl_, 
       expr2<val_type,d4,d3,l,k>      const& Rlk_) {
    typedef expr3<val_type,d1,d2,d3,i,j,k> ret_type;
    ret_type ret_ijk;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          ret_ijk(N1,N2,N3)=0;
          for (std::size_t n4 = 0; n4 < d4; ++n4){
            ret_ijk(N1,N2,N3) += Lijl_(N1,N2,n4) * Rlk_(n4,N3);
          }
        }
      }
    }
    return ret_ijk;
}



template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr3<val_type,d1,d2,d3,i,j,k> operator*(
       expr2<val_type,d1,d4,i,l>      const& Lil_, 
       expr3<val_type,d4,d2,d3,l,j,k> const& Rljk_) {
    typedef expr3<val_type,d1,d2,d3,i,j,k> ret_type;
    ret_type ret_ijk;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          ret_ijk(N1,N2,N3)=0;
          for (std::size_t n4 = 0; n4 < d4; ++n4){
            ret_ijk(N1,N2,N3) += Lil_(N1,n4) * Rljk_(n4,N2,N3);
          }
        }
      }
    }
    return ret_ijk;
}


template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
ST_ALWAYS_INLINE expr3<val_type,d1,d2,d3,i,j,k> operator*(
       expr1<val_type,d4,l>                const& Ll_, 
       expr4<val_type,d4,d1,d2,d3,l,i,j,k> const& Rlijk_) {
    typedef expr3<val_type,d1,d2,d3,i,j,k> ret_type;
    ret_type ret_ijk;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          ret_ijk(N1,N2,N3)=0;
          for (std::size_t n4 = 0; n4 < d4; ++n4){
            ret_ijk(N1,N2,N3) += Ll_(n4) * Rlijk_(n4,N1,N2,N3);
          }
        }
      }
    }
    return ret_ijk;
}


}

