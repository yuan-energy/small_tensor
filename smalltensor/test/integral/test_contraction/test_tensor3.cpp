#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor2<double, 3,3> obj1;
	tensor2<double, 3,3> obj2;
	tensor4<double, 3,3,3,3> obj3;
	tensor4<double, 3,3,3,3> obj4;

	obj2(2,2) = 2.;
	obj1(2,2) = 2.;

	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	Index<'l'> l;
	obj3(0,1,2,0) = 20;
	obj3(i,j,k,l) = obj3(i,j,k,l)+obj3(i,k,j,l) ;
	ASSERT_MSG(obj3(0,1,2,0)==20,"expr4 contraction2 operator error: obj1(i,j,m,n)*obj2(m,n,k,l)");

	cout<<"Done execution. Exiting..." <<endl;

	return 0;
}