#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor2<double, 3,3> obj1;
	tensor2<double, 3,3> obj2;
	tensor2<double, 3,3> obj3;
	obj1(2,2) = 3.;
	obj2(2,2) = 2.;
	Index<'i'> _i;
	Index<'j'> _j;
	obj3(_i,_j) = obj2(_i,_j) / 2;
	ASSERT_MSG(obj3(2,2)== 1,"tensor2(_i,_j) plus operator error");

	cout<<"Done execution. Exiting..." <<endl;

	return 0;
}