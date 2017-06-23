#ifndef TENSOR2_CONTRACT_TENSOR2_H_
#define TENSOR2_CONTRACT_TENSOR2_H_



template<typename Lij, typename Rij, typename val_type >
inline val_type Lij_contract_Rij( Lij const& ExprL,  Rij const& ExprR)
{   
	val_type res = 0;
	for(dimension_type n1 = 0 ; n1 < ExprL.get_dim1(); ++n1)
	{
		for(dimension_type n2 = 0 ; n2 < ExprL.get_dim2(); ++n2)
		{
			res += ExprL(n1,n2)*ExprR(n1,n2);
		}
	}
	return res;
}



#endif