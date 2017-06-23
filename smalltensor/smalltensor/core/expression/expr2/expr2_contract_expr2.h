#ifndef EXPR2_CONTRACT_EXPR2_H_
#define EXPR2_CONTRACT_EXPR2_H_

#define Lij Expr2<val_type,i,j>
#define Rij Expr2<val_type,i,j>

template <typename val_type, char i, char j>
inline const val_type 
operator* (Lij const& Lij_,  Rij const& Rij_){
	return Lij_contract_Rij<Lij,Rij, val_type>(Lij_, Rij_) ;
}



#undef Lij
#undef Rij


#endif