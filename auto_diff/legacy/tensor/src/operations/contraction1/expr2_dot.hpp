#pragma once


template <typename val_type, std::size_t d1, std::size_t d2, std::size_t d3, 
          char i, char j, char k>
inline expr2<val_type,d1,d2,i,j> operator* (
       expr3<val_type,d1,d2,d3,i,j,k> const& Lijk_,
       expr1<val_type,d3,k>           const& Rk_){
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        ret_ij(N1,N2)=0;
        for (std::size_t n3 = 0; n3 < d3; ++n3){
          ret_ij(N1,N2) += Lijk_(N1,N2,n3) * Rk_(n3);
        }
      }
    }
    return ret_ij;
}



template <typename val_type, std::size_t d1, std::size_t d2, std::size_t d3, 
          char i, char j, char k>
inline expr2<val_type,d1,d2,i,j> operator* (
       expr2<val_type,d1,d3,i,k> const& Lik_,  
       expr2<val_type,d3,d2,k,j> const& Rkj_){
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        ret_ij(N1,N2)=0;
        for (std::size_t n3 = 0; n3 < d3; ++n3){
          ret_ij(N1,N2) += Lik_(N1,n3) * Rkj_(n3,N2);
        }
      }
    }
    return ret_ij;
}




template <typename val_type, std::size_t d1, std::size_t d2, std::size_t d3, 
          char i, char j, char k>
inline expr2<val_type,d1,d2,i,j> operator* (
       expr1<val_type,d3,k> const& Lk_,
       expr3<val_type,d3,d1,d2,k,i,j> const& Rkij_){
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        ret_ij(N1,N2)=0;
        for (std::size_t n3 = 0; n3 < d3; ++n3){
          ret_ij(N1,N2) += Lk_(n3) * Rkij_(n3,N1,N2);
        }
      }
    }
    return ret_ij;
}


