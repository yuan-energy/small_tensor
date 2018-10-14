#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor4<double, 3, 3, 3, 3> obj1;
	tensor2<double, 3,3> obj2;
	obj1(1,2,1,2) = 9993;
	obj1(1,2,1,1) = 3;
	obj1(1,2,2,2) = 39;
	eindex<'i'> i;
	eindex<'j'> j;
	eindex<'k'> k;
	obj2(i,j) = obj1(i,j,k,k);
	ASSERT_MSG(obj2(1,2)==42,"tensor4(i,j,k,k) condense tensor error");


	return 0;
}