#ifndef EQUATE_TENSOR2_H_
#define EQUATE_TENSOR2_H_


template<typename L, typename R>
inline void Lij_equal_Rij(L & left_, const R & right_)
{

 	for(int n1 = 0; n1<left_.get_dim1();++n1)
		for(int n2 = 0; n2<left_.get_dim2();++n2){
			left_(n1,n2) = right_(n1,n2);
		}
}



#endif