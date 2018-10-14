#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor;
eindex<'i'> i;
eindex<'j'> j;
eindex<'k'> k;
eindex<'l'> l;

void test_const(stresstensor const& B)
{
	stresstensor A;
	stresstensor C = B;
	A(i,j) + C(i,j) ; 
	A(i,j) + B(i,j) ; 
}


int main(int argc, char const *argv[])
{
	tensor2<double, 3,3> obj1;
	tensor2<double, 3,3> obj2;
	tensor2<double, 3,3> obj3;

	obj2(2,2) = 2.;

	// Test 1
	obj1(2,2)= 1;
	obj3(i,j)=obj1(i,j) + obj2(i,j) / (obj2(k,l)*obj2(k,l)) ;
	ASSERT_MSG(obj3(2,2)==1.5,"tensor2(_i,_j) contraction1  operator error");
	
	cout<<"Done execution. Exiting..." <<endl;


	return 0;
}