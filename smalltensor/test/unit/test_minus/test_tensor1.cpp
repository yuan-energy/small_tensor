#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor1<double, 3> obj1;
	tensor1<double, 3> obj2;
	tensor1<double, 3> obj3;
	obj1(2) = 3.;
	obj2(2) = 2.;
	Index<'i'> _i;
	obj3(_i) = - obj1(_i);
	ASSERT_MSG(obj3(2)==-3,"tensor1 obj3(_i) minus operator error");
	ASSERT_MSG(obj2(2)== 2,"tensor1 obj2(_i) minus operator error");
	ASSERT_MSG(obj1(2)== 3,"tensor1 obj1(_i) minus operator error");

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