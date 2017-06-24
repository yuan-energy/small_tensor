#ifndef EXPR2_CONTRACT_EXPR2_H_
#define EXPR2_CONTRACT_EXPR2_H_

    
template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
val_type operator* (expr2<val_type,d1,d2,i,j> const& Lij_,  expr2<val_type,d1,d2,i,j> const& Rij_){
    val_type ret{0};
    for (std::size_t n1 = 0; n1 < d1; ++n1){
        for (std::size_t n2 = 0; n2 < d2; ++n2){
            ret += Lij_(n1,n2) * Rij_(n1,n2);
        }
    }
    return ret;
}

template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
val_type operator* (expr2<val_type,d1,d2,i,j> const& Lij_,  expr2<val_type,d2,d1,j,i> const& Rji_){
    val_type ret{0};
    for (std::size_t n1 = 0; n1 < d1; ++n1){
        for (std::size_t n2 = 0; n2 < d2; ++n2){
            ret += Lij_(n1,n2) * Rji_(n2,n1);
        }
    }
    return ret;
}



#endif