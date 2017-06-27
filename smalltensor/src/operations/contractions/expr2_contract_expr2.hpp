#ifndef EXPR2_CONTRACT_EXPR2_H_
#define EXPR2_CONTRACT_EXPR2_H_

    
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

template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
inline val_type operator* (expr2<val_type,d1,d2,i,j> const& Lij_,  
                           expr2<val_type,d2,d1,j,i> const& Rji_){
    val_type ret{0};
    for (std::size_t n1 = 0; n1 < d1; ++n1){
        for (std::size_t n2 = 0; n2 < d2; ++n2){
            ret += Lij_(n1,n2) * Rji_(n2,n1);
        }
    }
    return ret;
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
            for (std::size_t n3 = 0; n3 < d3; ++n3)
            {
                ret_ij(N1,N2) += Lik_(N1,n3) * Rkj_(n3,N2);
            }
        }
    }
    return ret_ij;
}

template <typename val_type, std::size_t d1, std::size_t d2, std::size_t d3, 
          char i, char j, char k>
inline expr2<val_type,d1,d2,i,j> operator* (
                                  expr2<val_type,d1,d3,i,k> const& Lik_,  
                                  expr2<val_type,d2,d3,j,k> const& Rjk_){
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
        for (std::size_t N2 = 0; N2 < d2; ++N2){
            for (std::size_t n3 = 0; n3 < d3; ++n3)
            {
                ret_ij(N1,N2) += Lik_(N1,n3) * Rjk_(N2,n3);
            }
        }
    }
    return ret_ij;
}

template <typename val_type, std::size_t d1, std::size_t d2, 
          std::size_t d3, char i, char j, char k>
inline expr2<val_type,d1,d2,i,j> operator* (
                                  expr2<val_type,d3,d1,k,i> const& Lki_,  
                                  expr2<val_type,d2,d3,j,k> const& Rjk_){
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
        for (std::size_t N2 = 0; N2 < d2; ++N2){
            for (std::size_t n3 = 0; n3 < d3; ++n3)
            {
                ret_ij(N1,N2) += Lki_(n3,N1) * Rjk_(N2,n3);
            }
        }
    }
    return ret_ij;
}

template <typename val_type, std::size_t d1, std::size_t d2, std::size_t d3, 
          char i, char j, char k>
inline expr2<val_type,d1,d2,i,j> operator* (
                                  expr2<val_type,d3,d1,k,i> const& Lki_,  
                                  expr2<val_type,d3,d2,k,j> const& Rkj_){
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
        for (std::size_t N2 = 0; N2 < d2; ++N2){
            for (std::size_t n3 = 0; n3 < d3; ++n3)
            {
                ret_ij(N1,N2) += Lki_(n3,N1) * Rkj_(n3,N2);
            }
        }
    }
    return ret_ij;
}

#endif