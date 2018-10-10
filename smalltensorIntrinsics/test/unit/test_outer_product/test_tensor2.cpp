#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	tensor1<double, 3> obj1;
	tensor2<double, 3,3> obj2;
	tensor3<double, 3,3,3> obj3;
	obj1(2) = 3.;
	obj2(2,2) = 2.;
	Index<'i'> _i;
	Index<'j'> _j;
	Index<'k'> _k;
	obj3(_i,_j,_k) = obj2(_i,_j) * obj1(_k);
	obj3(_i,_j,_k) = obj1(_i) * obj2(_j,_k) ;
	// cout<<"obj3(2,2) = " << obj3(2,2) <<endl;
	ASSERT_MSG(obj3(2,2,2)== 6,"tensor2() outer product error");

	cout<<"Done execution. Exiting..." <<endl;


	return 0;
}