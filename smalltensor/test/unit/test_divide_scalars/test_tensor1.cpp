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
	obj3(_i) = obj2(_i) / 2;
	ASSERT_MSG(obj3(2)== 1,"tensor1 obj3(_i) plus operator error");
	ASSERT_MSG(obj2(2)== 2,"tensor1 obj2(_i) plus operator error");
	ASSERT_MSG(obj1(2)== 3,"tensor1 obj1(_i) plus operator error");

	cout<<"Done execution. Exiting..." <<endl;



	return 0;
}