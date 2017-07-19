#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	tensor2<double, 3,3> obj1;
	tensor2<double, 3,3> obj2;
	tensor2<double, 3,3> obj3;
	obj1(2,2) = 3.;
	obj2(2,2) = 2.;
	Index<'i'> _i;
	Index<'j'> _j;
	obj3(_i,_j) = obj2(_i,_j) * 2;
	// cout<<"obj3(2,2) = " << obj3(2,2) <<endl;
	ASSERT_MSG(obj3(2,2)== 4,"tensor2(_i,_j) plus operator error");

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