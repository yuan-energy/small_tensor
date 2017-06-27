#ifndef EXPR1_CONTRACT_EXPR1_H_
#define EXPR1_CONTRACT_EXPR1_H_

template <typename val_type, std::size_t d1, char i>
inline val_type operator*(expr1<val_type,d1,i>const& Li_, expr1<val_type,d1,i> const& Ri_) {
    val_type ret{0};
    for (std::size_t n1 = 0; n1 < d1; ++n1){
        ret += Li_(n1) * Ri_(n1);
    }
    return ret;
}


#endif