#pragma once

template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          std::size_t d5,
          char i, char j, char k, char l, char m>
ST_ALWAYS_INLINE expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator*(
       expr4<val_type,d1,d2,d3,d5,i,j,k,m>const& Lijkm_, 
       expr2<val_type,d5,d4,m,l> const& Rml_) {
    typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
    ret_type ret_ijkl;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          for (std::size_t N4 = 0; N4 < d4; ++N4){
            ret_ijkl(N1,N2,N3,N4)=0;
            for (std::size_t n5 = 0; n5 < d5; ++n5){
              ret_ijkl(N1,N2,N3,N4) += Lijkm_(N1,N2,N3,n5) * Rml_(n5,N4);
            }
          }
        }
      }
    }
    return ret_ijkl;
}



template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          std::size_t d5,
          char i, char j, char k, char l, char m>
ST_ALWAYS_INLINE expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator*(
       expr3<val_type,d1,d2,d5,i,j,m> const& Lijm_, 
       expr3<val_type,d5,d3,d4,m,k,l> const& Rmkl_) {
    typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
    ret_type ret_ijkl;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          for (std::size_t N4 = 0; N4 < d4; ++N4){
            ret_ijkl(N1,N2,N3,N4)=0;
            for (std::size_t n5 = 0; n5 < d5; ++n5){
              ret_ijkl(N1,N2,N3,N4) += Lijm_(N1,N2,n5) * Rmkl_(n5,N3,N4);
            }
          }
        }
      }
    }
    return ret_ijkl;
}



template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          std::size_t d5,
          char i, char j, char k, char l, char m>
ST_ALWAYS_INLINE expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator*(
       expr2<val_type,d1,d5,i,m> const& Lim_, 
       expr4<val_type,d5,d2,d3,d4,m,j,k,l> const& Rmjkl_) {
    typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
    ret_type ret_ijkl;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          for (std::size_t N4 = 0; N4 < d4; ++N4){
            ret_ijkl(N1,N2,N3,N4)=0;
            for (std::size_t n5 = 0; n5 < d5; ++n5){
              ret_ijkl(N1,N2,N3,N4) += Lim_(N1,n5) * Rmjkl_(n5,N2,N3,N4);
            }
          }
        }
      }
    }
    return ret_ijkl;
}

