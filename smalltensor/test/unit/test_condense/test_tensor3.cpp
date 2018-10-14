#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor3<double, 3, 3, 3> obj1;
	tensor1<double, 3> obj2;
	obj1(1,2,1) = 3;
	obj1(1,1,1) = 42;
	Index<'i'> i;
	Index<'j'> j;
	obj2(i) = obj1(i,j,j);
	ASSERT_MSG(obj2(1)==42,"tensor3(i,j,j) condense tensor error");

	return 0;
}