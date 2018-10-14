#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor2<double, 3, 3> obj1;
	obj1(1,2) = 3;
	obj1(1,1) = 42;
	Index<'i'> i;
	ASSERT_MSG(obj1(i,i)==42,"tensor2(n1,n1) condense tensor error");

	return 0;
}