#ifndef EXPR2_CONTRACT_EXPR2_H_
#define EXPR2_CONTRACT_EXPR2_H_

#define Lij Expr2<val_type,i,j>
#define Rij Expr2<val_type,i,j>
#define Rji Expr2<val_type,j,i>
    template <typename val_type, char i, char j>
    inline const val_type 
    operator* (Lij const& Lij_,  Rij const& Rij_){
        return Lij_contract_Rij<Lij,Rij, val_type>(Lij_, Rij_) ;
    }
    template <typename val_type, char i, char j>
    inline const val_type 
    operator* (Lij const& Lij_,  Rji const& Rji_){
        return Lij_contract_Rji<Lij,Rji, val_type>(Lij_, Rji_) ;
    }
#undef Lij
#undef Rij
#undef Rji













#endif