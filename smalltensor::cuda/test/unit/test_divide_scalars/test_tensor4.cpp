#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
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
	obj3(_i,_j,_k,_l) = obj2(_i,_j,_k,_l) /2;
	ASSERT_MSG(obj3(2,1,1,2)==1,"tensor4(_i,_j,_k,_l) plus operator error");

	cout<<"Done execution. Exiting..." <<endl;


	return 0;
}