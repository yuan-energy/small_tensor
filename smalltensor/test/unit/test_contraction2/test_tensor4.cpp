#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor4<double,3, 3,3,3> obj1;
	tensor4<double,3, 3,3,3> obj2;
	tensor4<double,3, 3,3,3> obj3;

	eindex<'i'> i;
	eindex<'j'> j;
	eindex<'k'> k;
	eindex<'l'> l;
	eindex<'m'> m;
	eindex<'n'> n;

	// Test 1
	obj1(1,2,2,2) = 1;
	obj2(2,2,1,2) = 3;
	obj3(i,j,k,l)= 	obj1(i,j,m,n)*obj2(m,n,k,l);
	ASSERT_MSG(obj3(1,2,1,2)==3,"expr4 contraction2 operator error: obj1(i,j,m,n)*obj2(m,n,k,l)");
	
	return 0;
}