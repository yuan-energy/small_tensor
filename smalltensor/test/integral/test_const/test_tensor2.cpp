#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor2<double, 3,3> obj1;
	tensor2<double, 3,3> obj2;
	tensor2<double, 3,3> obj3("identity") ;
	tensor4<double, 3,3,3,3> Ee ;

	obj2(2,2) = 2.;
	eindex<'i'> i;
	eindex<'j'> j;
	eindex<'k'> k;
	eindex<'l'> l;

	// Test 1
	obj1(2,2)= 1;
	obj3(i,j)=obj1(i,j) + obj2(i,j) * 3;
	obj3(i,j)=obj1(i,j) + 3 * obj2(i,j) ;
	ASSERT_MSG(obj3(2,2)==7,"tensor2(_i,_j) contraction1  operator error");
	

	// Test 2
	double mu=0.2;
	Ee(i,j,k,l) = mu * (obj3(i,k) * obj3(j,l) ) + obj3(i,l) * obj3(j,k) ;
	cout<<"Done execution. Exiting..." <<endl;

	return 0;
}