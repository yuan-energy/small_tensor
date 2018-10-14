#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor4<double,3,3,3,3> obj1;
	tensor2<double,3,3> obj2;
	tensor2<double,3,3> obj3;
	tensor2<double,3,3> obj4;

	Index<'i'> i;
	Index<'j'> j;
	// Index<'k'> k;
	// Index<'l'> l;
	Index<'m'> m;
	Index<'n'> n;

	// Test 1
	obj1(1,2,2,2) = 1;
	obj3(1,2) = 2;
	obj2(2,2) = 3;
	double ret = obj3(i,j)*obj1(i,j,m,n)*obj2(m,n);
	ASSERT_MSG( ret==6,"expr4 contraction2 operator error: obj1(i,j,m,n)*obj2(m,n,k,l)");
	
	obj4(i,j) = obj1(i,j,m,n)*obj2(m,n) - obj3(i,j) ;
	ASSERT_MSG( obj4(1,2) ==1,"expr4 contraction2 operator error: obj1(i,j,m,n)*obj2(m,n,k,l)");
	
	return 0;
}