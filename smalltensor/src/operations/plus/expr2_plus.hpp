#ifndef EXPR2_PLUS_H_
#define EXPR2_PLUS_H_


template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
inline expr2<val_type,d1,d2,i,j> operator+(
                                  expr2<val_type,d1,d2,i,j> const& Lij_, 
                                  expr2<val_type,d1,d2,i,j> const& Rij_){
	typedef expr2<val_type,d1,d2,i,j> ret_type;
	ret_type ret_ij;
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			ret_ij(n1,n2) = Lij_(n1,n2) + Rij_(n1,n2);
		}
	}
	return ret_ij;
}



// template <typename val_type, std::size_t d1, std::size_t d2, char i, char j>
// inline expr2<val_type,d1,d2,i,j> operator-(
//                                   expr2<val_type,d1,d2,i,j> const& Lij_, 
//                                   expr2<val_type,d2,d1,j,i> const& Rji_){
// 	typedef expr2<val_type,d1,d2,i,j> ret_type;
// 	ret_type ret_ij;
// 	for (std::size_t n1 = 0; n1 < d1; ++n1){
// 		for (std::size_t n2 = 0; n2 < d2; ++n2){
// 			ret_ij(n1,n2) = Lij_(n1,n2) - Rji_(n2,n1);
// 		}
// 	}
// 	return ret_ij;
// }



#endif