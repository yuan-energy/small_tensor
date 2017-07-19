#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	tensor3<double, 3,3,3> obj1;
	tensor3<double, 3,3,3> obj2;
	tensor3<double, 3,3,3> obj3;
	obj1(2,1,2) = 3.;
	obj2(2,1,2) = 2.;
	Index<'i'> _i;
	Index<'j'> _j;
	Index<'k'> _k;
	obj3(_i,_j,_k) = obj2(_i,_j,_k) / 2;
	ASSERT_MSG(obj3(2,1,2)==1,"tensor3(_i,_j,_k) plus operator error");

	cout<<"Done execution. Exiting..." <<endl;

	return 0;
}