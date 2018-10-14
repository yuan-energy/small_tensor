#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor4<double, 3,3,3,3> obj1;
	tensor4<double, 3,3,3,3> obj2;
	tensor4<double, 3,3,3,3> obj3;
	obj1(2,1,1,2) = 3.;
	obj2(2,1,1,2) = 2.;
	Index<'i'> _i;
	Index<'j'> _j;
	Index<'k'> _k;
	Index<'l'> _l;
	obj3(_i,_j,_k,_l) = obj2(_i,_j,_k,_l) - obj1(_i,_j,_k,_l);
	ASSERT_MSG(obj3(2,1,1,2)==-1,"tensor4(_i,_j,_k,_l) minus operator error");

	cout<<"Done execution. Exiting..." <<endl;

	// Index<'i'> i;
	// Index<'j'> j;

	// tensor1<double, 3> L;
	// tensor1<double, 3> R;
	// L(0,0) = 9; R(0,0) = 2;
	// double ret = L(i,j) * R(i,j);
	// ret = L(i,j) * R(j,i);
	// ASSERT_MSG(ret==18,"expr2 tensor2 contraction error");


	return 0;
}