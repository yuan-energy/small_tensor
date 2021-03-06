#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor3<double, 3,3,3> obj1;
	tensor3<double, 3,3,3> obj2;
	tensor3<double, 3,3,3> obj3;
	obj1(2,1,2) = 3.;
	obj2(2,1,2) = 2.;
	eindex<'i'> _i;
	eindex<'j'> _j;
	eindex<'k'> _k;
	obj3(_i,_j,_k) = - obj1(_i,_j,_k);
	// cout<<"obj3(_i,_j,_k)="<<obj3(2,1,2)<<endl;
	ASSERT_MSG(obj3(2,1,2)==-3,"tensor3(_i,_j,_k) minus operator error");

	cout<<"Done execution. Exiting..." <<endl;

	// eindex<'i'> i;
	// eindex<'j'> j;

	// tensor1<double, 3> L;
	// tensor1<double, 3> R;
	// L(0,0) = 9; R(0,0) = 2;
	// double ret = L(i,j) * R(i,j);
	// ret = L(i,j) * R(j,i);
	// ASSERT_MSG(ret==18,"expr2 tensor2 contraction error");


	return 0;
}